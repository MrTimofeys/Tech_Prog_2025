#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>

class DatabaseManager;

class DatabaseManagerDestroyer
{
private:
    DatabaseManager* p_instance;
public:
    ~DatabaseManagerDestroyer();
    void initialize(DatabaseManager* p);
};

class DatabaseManager
{
private:
    static DatabaseManager* p_instance;
    static DatabaseManagerDestroyer destroyer;
    QSqlDatabase m_db;

    QString hashPassword(const QString& password);
    friend class TestMyTcpServer;


protected:
    DatabaseManager();
    ~DatabaseManager();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    friend class DatabaseManagerDestroyer;
    friend class TestMyTcpServer;

public:
    static DatabaseManager* getInstance();
    bool init(const QString& dbName = "users.db");

    bool registerUser(const QString& username, const QString& password, const QString& email);
    bool authenticateUser(const QString& username, const QString& password);
    bool updateUserPassword(const QString& username, const QString& newPassword);
    QString getEmailByUsername(const QString& username);
};

#endif // DATABASEMANAGER_H
