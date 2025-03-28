#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H


#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QCryptographicHash>
#include "equationsolver.h"


class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();


private:
    QTcpServer * mTcpServer;
    QList<QTcpSocket*> mClients;
    QSqlDatabase db;

    void setupDatabase();
    bool registerUser(const QString &username, const QString &password, const QString &email);
    bool authenticateUser(const QString &username, const QString &password);
    QString hashPassword(const QString &password);

    static double mathFunc(double x){return cos(x);}
};

#endif // MYTCPSERVER_H
