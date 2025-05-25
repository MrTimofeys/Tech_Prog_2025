#include "mytcpserver.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QSslSocket>
#include <QtConcurrent>

MyTcpServer::MyTcpServer(QObject *parent, bool testMode)
    : QObject(parent)
{
    DatabaseManager::getInstance()->init(testMode ? "test_users.db" : "users.db");

    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "Server is not started";
    } else {
        qDebug() << "Server is started";
    }
}

MyTcpServer::~MyTcpServer()
{
    for (auto client : mClients) {
        client->close();
        delete client;
    }
    mTcpServer->close();
}

void MyTcpServer::slotNewConnection()
{
    QTcpSocket *clientSocket = mTcpServer->nextPendingConnection();
    mClients.append(clientSocket);

    connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);

    clientSocket->write("Connected to registration/auth server!\n");
}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    mClients.removeOne(clientSocket);
    clientSocket->close();
    clientSocket->deleteLater();
}

void MyTcpServer::slotServerRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
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
        bool success = DatabaseManager::getInstance()->registerUser(username, password, email);
        responseJson["message"] = success ? "User registered successfully!" : "Registration failed.";

    } else if (command == "login") {
        bool success = DatabaseManager::getInstance()->authenticateUser(username, password);
        responseJson["message"] = success ? "Login successful!" : "Invalid username or password.";

    } else if (command == "solve") {
        QString funcName = json["function"].toString();
        double x0 = json["x0"].toDouble();
        double tolerance = json["tolerance"].toDouble();
        int maxIterations = json["maxIterations"].toInt();

        double root = equationSolver::solveIterationMethod(funcName, x0, tolerance, maxIterations);
        responseJson["message"] = std::isnan(root) ? "No convergence or invalid function name" : "Solution found";
        if (!std::isnan(root)) responseJson["root"] = root;

    } else if (command == "send_code") {
        QString email = DatabaseManager::getInstance()->getEmailByUsername(username);
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
        bool success = DatabaseManager::getInstance()->updateUserPassword(username, password);
        responseJson["message"] = success ? "Password updated!" : "Password update failed.";

    } else {
        responseJson["message"] = "Unknown command";
    }

    QJsonDocument responseDoc(responseJson);
    clientSocket->write(responseDoc.toJson());
    clientSocket->flush();
}

QString MyTcpServer::generateRandomCode(int length)
{
    const QString chars("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
    QString code;
    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->bounded(chars.length());
        code.append(chars.at(index));
    }
    return code;
}

void MyTcpServer::sendEmail(const QString &to, const QString &code)
{
    QSslSocket socket;
    socket.connectToHostEncrypted("smtp.yandex.ru", 465);
    if (!socket.waitForEncrypted(3000)) {
        qDebug() << "SSL handshake failed:" << socket.errorString();
        return;
    }

    auto write = [&](const QString &data) {
        socket.write((data + "\r\n").toUtf8());
        if (!socket.waitForBytesWritten(3000)) return false;
        if (!socket.waitForReadyRead(3000)) return false;
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
