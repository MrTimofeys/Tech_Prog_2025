#include "funcsforclient.h"
#include "clientmanager.h"
#include <QString>
#include <QDebug>

bool auth(QString login, QString password)
{
    ClientManager* client = ClientManager::getInstance();
    
    // Подключаемся к серверу, если еще не подключены
    if (!client->isConnected()) {
        if (!client->connectToServer()) {
            qDebug() << "Failed to connect to server";
            return false;
        }
    }

    // Отправляем запрос на авторизацию
    bool result = client->loginUser(login, password);
    
    // Ждем ответа от сервера
    QObject::connect(client, &ClientManager::loginResult, [&result](bool success, const QString& message) {
        result = success;
        qDebug() << "Login result:" << message;
    });

    return result;
}

bool reg(QString login, QString password, QString email)
{
    ClientManager* client = ClientManager::getInstance();
    
    // Подключаемся к серверу, если еще не подключены
    if (!client->isConnected()) {
        if (!client->connectToServer()) {
            qDebug() << "Failed to connect to server";
            return false;
        }
    }

    // Отправляем запрос на регистрацию
    bool result = client->registerUser(login, password, email);
    
    // Ждем ответа от сервера
    QObject::connect(client, &ClientManager::registrationResult, [&result](bool success, const QString& message) {
        result = success;
        qDebug() << "Registration result:" << message;
    });

    return result;
}
