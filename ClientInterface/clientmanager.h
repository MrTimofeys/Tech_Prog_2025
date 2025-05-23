#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHostAddress>

class ClientManager : public QObject
{
    Q_OBJECT
private:
    static ClientManager* instance;
    QTcpSocket* socket;
    QString storedVerificationCode;
    explicit ClientManager(QObject *parent = nullptr);
    ~ClientManager();

public:
    static ClientManager* getInstance();
    static void destroyInstance();
    bool ClientManager::solveEquation(const QString &functionName,
                                      double x0,
                                      double tolerance,
                                      int maxIterations);
    // bool connectToServer(const QString& host = "localhost", quint16 port = 33333);
    bool connectToServer(const QString& host = "77.222.47.216", quint16 port = 33333);
    void disconnectFromServer();
    bool isConnected() const;

    bool registerUser(const QString& username, const QString& password, const QString& email);
    bool loginUser(const QString& username, const QString& password);

    // Новые методы для восстановления пароля
    bool sendVerificationCode(const QString& username);
    bool resetPassword(const QString& username, const QString& code, const QString& newPassword);

    void clearStoredVerificationCode() { storedVerificationCode.clear(); }
    QString getStoredVerificationCode() const { return storedVerificationCode; }

signals:
    void connectionStatusChanged(bool connected);
    void registrationResult(bool success, const QString& message);
    void loginResult(bool success, const QString& message);
    void verificationCodeResult(bool success, const QString& message);
    void passwordResetResult(bool success, const QString& message);
    void equationSolved(bool success, double root, const QString& message);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);

private:
    void sendRequest(const QJsonObject& request);
    void processResponse(const QJsonObject& response);
};

#endif // CLIENTMANAGER_H 
