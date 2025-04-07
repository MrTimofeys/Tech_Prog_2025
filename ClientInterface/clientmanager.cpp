#include "clientmanager.h"
#include <QDebug>

ClientManager* ClientManager::instance = nullptr;

ClientManager* ClientManager::getInstance()
{
    if (!instance) {
        instance = new ClientManager();
    }
    return instance;
}

void ClientManager::destroyInstance()
{
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

ClientManager::ClientManager(QObject *parent)
    : QObject(parent)
    , socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, &ClientManager::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &ClientManager::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &ClientManager::onReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
            this, &ClientManager::onError);
}

ClientManager::~ClientManager()
{
    disconnectFromServer();
    delete socket;
}

bool ClientManager::connectToServer(const QString& host, quint16 port)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        return true;
    }

    socket->connectToHost(host, port);
    return socket->waitForConnected(5000);
}

void ClientManager::disconnectFromServer()
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
        socket->waitForDisconnected(5000);
    }
}

bool ClientManager::isConnected() const
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

bool ClientManager::registerUser(const QString& username, const QString& password, const QString& email)
{
    if (!isConnected()) {
        emit registrationResult(false, "Not connected to server");
        return false;
    }

    QJsonObject request;
    request["command"] = "register";
    request["username"] = username;
    request["password"] = password;
    request["email"] = email;

    sendRequest(request);
    return true;
}

bool ClientManager::loginUser(const QString& username, const QString& password)
{
    if (!isConnected()) {
        emit loginResult(false, "Not connected to server");
        return false;
    }

    QJsonObject request;
    request["command"] = "login";
    request["username"] = username;
    request["password"] = password;

    sendRequest(request);
    return true;
}

void ClientManager::onConnected()
{
    emit connectionStatusChanged(true);
}

void ClientManager::onDisconnected()
{
    emit connectionStatusChanged(false);
}

void ClientManager::onReadyRead()
{
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isObject()) {
        processResponse(doc.object());
    }
}

void ClientManager::onError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Socket error:" << socketError << socket->errorString();
    emit connectionStatusChanged(false);
}

void ClientManager::sendRequest(const QJsonObject& request)
{
    QJsonDocument doc(request);
    QByteArray data = doc.toJson();
    socket->write(data);
    socket->flush();
}

void ClientManager::processResponse(const QJsonObject& response)
{
    QString message = response["message"].toString();
    
    if (message.contains("registered successfully")) {
        emit registrationResult(true, message);
    } else if (message.contains("Error")) {
        emit registrationResult(false, message);
    } else if (message.contains("Login successful")) {
        emit loginResult(true, message);
    } else if (message.contains("Invalid")) {
        emit loginResult(false, message);
    }
} 