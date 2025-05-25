#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QtConcurrent/QtConcurrent>

#include "databasemanager.h"
#include "equationsolver.h"

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr, bool testMode = false);
    ~MyTcpServer();

public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();

private:
    QTcpServer *mTcpServer;
    QList<QTcpSocket*> mClients;

    QString generateRandomCode(int length);
    void sendEmail(const QString &to, const QString &code);
    friend class TestMyTcpServer;
};

#endif // MYTCPSERVER_H
