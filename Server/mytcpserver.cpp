
#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include "equationsolver.h"
#include <QRandomGenerator>
#include <QSslSocket>
#include <QByteArray>
#include <QtConcurrent>

MyTcpServer::~MyTcpServer()
{
    for (auto client : mClients) {
        client->close();
        delete client;
    }
    mTcpServer->close();
    db.close();
}

MyTcpServer::MyTcpServer(QObject *parent, bool testMode)
    : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }

    db = QSqlDatabase::addDatabase("QSQLITE");

    if (testMode) {
        db.setDatabaseName("test_users.db");
    } else {
        db.setDatabaseName("users.db");
    }

    if (!db.open()) {
        qDebug() << "Database is not open!" << db.lastError();
        return;
    }

    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "username TEXT PRIMARY KEY, "
               "password TEXT, "
               "email TEXT)");
}


void MyTcpServer::setupDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");

    if (!db.open()) {
        qDebug() << "Ошибка открытия БД:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    QString createTableSQL =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE, "
        "password TEXT, "
        "email TEXT UNIQUE)";
    if (!query.exec(createTableSQL)) {
        qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
    } else {
        qDebug() << "Таблица готова!";
    }
}

void MyTcpServer::slotNewConnection() {
    QTcpSocket* clientSocket = mTcpServer->nextPendingConnection();
    mClients.append(clientSocket);

    connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);

    clientSocket->write("Connected to registration/auth server!\n");
}

void MyTcpServer::slotServerRead() {
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QByteArray requestData = clientSocket->readAll();
    qDebug() << "Received data:" << requestData;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(requestData);
    QJsonObject json = jsonDoc.object();

    QString command = json["command"].toString();
    QString username = json["username"].toString();
    QString password = json["password"].toString();
    QString email = json["email"].toString();

    QJsonObject responseJson;

    if (command == "register") {
        if (registerUser(username, password, email)) {
            responseJson["message"] = "User registered successfully!";
        } else {
            responseJson["message"] = "Error: Username or email already exists.";
        }
    } else if (command == "login") {
        if (authenticateUser(username, password)) {
            responseJson["message"] = "Login successful!";
        } else {
            responseJson["message"] = "Invalid username or password.";
        }
    }  else if (command == "solve") {
    QString funcName = json["function"].toString();
    double x0 = json["x0"].toDouble();
    double tolerance = json["tolerance"].toDouble();
    int maxIterations = json["maxIterations"].toInt();

    double root = equationSolver::solveIterationMethod(funcName, x0, tolerance, maxIterations);

    if (!std::isnan(root)) {
        responseJson["root"] = root;
        responseJson["message"] = "Solution found";
    } else {
        responseJson["message"] = "No convergence or invalid function name";
    }
} else if (command == "send_code") {
        QString email = getEmailByUsername(username);

        if (email.isEmpty()) {
            responseJson["message"] = "Error: Email not found for this username.";
        } else {
            QString verificationCode = generateRandomCode(6);

            responseJson["message"] = "Verification code sent to email!";
            responseJson["code"] = verificationCode;

            QtConcurrent::run([=]() {
                sendEmail(email, verificationCode);
            });
        }

    } else if (command == "update_password") {
        QString newPassword = password;

        qDebug() << "Updating password for username:" << username;
        qDebug() << "New password:" << newPassword;

        if (updateUserPassword(username, newPassword)) {
            responseJson["message"] = "Password updated successfully!";
        } else {
            responseJson["message"] = "Failed to update password.";
        }
    }

    else {
        responseJson["message"] = "Unknown command";
    }

    QJsonDocument responseDoc(responseJson);
    clientSocket->write(responseDoc.toJson());
    clientSocket->flush();
}

void MyTcpServer::slotClientDisconnected() {
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    mClients.removeOne(clientSocket);
    clientSocket->close();
    clientSocket->deleteLater();
}

QString MyTcpServer::hashPassword(const QString &password) {
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

bool MyTcpServer::registerUser(const QString &username, const QString &password, const QString &email) {
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO users (username, password, email) VALUES (:username, :password, :email)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashPassword(password));
    query.bindValue(":email", email);

    qDebug() << "Executing query: " << query.lastQuery();
    qDebug() << "Username: " << username << ", Email: " << email;

    if (!query.exec()) {
        qDebug() << "Ошибка регистрации:" << query.lastError().text();
        return false;
    }
    return true;
}

bool MyTcpServer::authenticateUser(const QString &username, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec() || !query.next()) {
        return false;
    }

    QString storedHashedPassword = query.value(0).toString();
    return storedHashedPassword == hashPassword(password);
}

void MyTcpServer::sendEmail(const QString &to, const QString &code) {
    QSslSocket socket;

    socket.connectToHostEncrypted("smtp.yandex.ru", 465);
    if (!socket.waitForEncrypted(3000)) {
        qDebug() << "SSL handshake failed:" << socket.errorString();
        return;
    }

    auto write = [&](const QString &data) {
        socket.write((data + "\r\n").toUtf8());
        if (!socket.waitForBytesWritten(3000)) {
            qDebug() << "Write failed:" << socket.errorString();
            return false;
        }
        if (!socket.waitForReadyRead(3000)) {
            qDebug() << "No response:" << socket.errorString();
            return false;
        }
        qDebug() << "Server:" << socket.readAll();
        return true;
    };

    write("EHLO yandex.ru");
    write("AUTH LOGIN");
    write(QByteArray("timp2025@yandex.ru").toBase64());
    write(QByteArray("metvfuyxyekxuqzr").toBase64());
    write("MAIL FROM: <timp2025@yandex.ru>");
    write("RCPT TO:<" + to + ">");
    write("DATA");
    write("From: MyApp <timp2025@yandex.ru>");
    write("To: " + to);
    write("Subject: Verification Code");
    write("");
    write("Your verification code: " + code);
    write(".");
    write("QUIT");
}
QString MyTcpServer::generateRandomCode(int length) {
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
    QString code;
    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->bounded(possibleCharacters.length());
        code.append(possibleCharacters.at(index));
    }
    return code;
}

bool MyTcpServer::updateUserPassword(const QString &username, const QString &newPassword) {
    QString hashedPassword = hashPassword(newPassword);

    QSqlQuery query;
    query.prepare("UPDATE users SET password = :password WHERE username = :username");
    query.bindValue(":password", hashedPassword);
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Failed to update password:" << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "No user found with username:" << username;
        return false;
    }

    return true;
}
QString MyTcpServer::getEmailByUsername(const QString &username) {
    QSqlQuery query;
    query.prepare("SELECT email FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }

    return QString();
}

