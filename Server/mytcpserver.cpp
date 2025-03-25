#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

MyTcpServer::~MyTcpServer()
{
    for (auto client : mClients) {
        client->close();
        delete client;
    }
    mTcpServer->close();
    db.close();
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent) {
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }

    setupDatabase();
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
        qDebug() << "Таблица users готова!";
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
    } else {
        responseJson["message"] = "Unknown command.";
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

