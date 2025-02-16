#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include<QString>

MyTcpServer::~MyTcpServer()
{
    for (auto client : mClients){
        client->close();
        delete client;
    }
    mTcpServer->close();
    //server_status=0;
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        //server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
    //   if(server_status==1){
    QTcpSocket* clientSocket = mTcpServer->nextPendingConnection();
    mClients.append(clientSocket);
    connect(clientSocket, &QTcpSocket::readyRead,this,&MyTcpServer::slotServerRead);
    connect(clientSocket,&QTcpSocket::disconnected,this,&MyTcpServer::slotClientDisconnected);

    clientSocket->write("Hello, World!!! I am echo server!\r\n");

    // }
}

void MyTcpServer::slotServerRead(){
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QString res = "";
    while(clientSocket->bytesAvailable()>0)
    {
        QByteArray array =clientSocket->readAll();
        qDebug()<<array<<"\n";
        if(array=="\x01")
        {
            clientSocket->write(res.toUtf8());
            res = "";
        }
        else
            res.append(array);
    }
    clientSocket->write(res.toUtf8());
}

void MyTcpServer::slotClientDisconnected(){
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;
    mClients.removeOne(clientSocket);
    clientSocket->close();
    clientSocket->deleteLater();
}
