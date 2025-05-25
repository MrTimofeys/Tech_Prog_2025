#include "databasemanager.h"

DatabaseManager* DatabaseManager::p_instance = nullptr;
DatabaseManagerDestroyer DatabaseManager::destroyer;

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager()
{
    if (m_db.isOpen())
        m_db.close();
}

DatabaseManagerDestroyer::~DatabaseManagerDestroyer()
{
    delete p_instance;
}

void DatabaseManagerDestroyer::initialize(DatabaseManager* p)
{
    p_instance = p;
}

DatabaseManager* DatabaseManager::getInstance()
{
    if (!p_instance) {
        p_instance = new DatabaseManager();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

bool DatabaseManager::init(const QString& dbName)
{
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        m_db = QSqlDatabase::database();
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName(dbName);
    }

    if (!m_db.open()) {
        qDebug() << "Database open failed:" << m_db.lastError();
        return false;
    }

    QSqlQuery query(m_db);
    return query.exec("CREATE TABLE IF NOT EXISTS users ("
                      "username TEXT PRIMARY KEY, "
                      "password TEXT, "
                      "email TEXT UNIQUE)");
}

QString DatabaseManager::hashPassword(const QString& password)
{
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

bool DatabaseManager::registerUser(const QString& username, const QString& password, const QString& email)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO users (username, password, email) "
                  "VALUES (:username, :password, :email)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashPassword(password));
    query.bindValue(":email", email);
    return query.exec();
}

bool DatabaseManager::authenticateUser(const QString& username, const QString& password)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec() || !query.next()) return false;
    return query.value(0).toString() == hashPassword(password);
}

bool DatabaseManager::updateUserPassword(const QString& username, const QString& newPassword)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE users SET password = :password WHERE username = :username");
    query.bindValue(":password", hashPassword(newPassword));
    query.bindValue(":username", username);
    return query.exec() && query.numRowsAffected() > 0;
}

QString DatabaseManager::getEmailByUsername(const QString& username)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT email FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return {};
}
