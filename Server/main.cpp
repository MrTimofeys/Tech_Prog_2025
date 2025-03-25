
#include <QCoreApplication>
#include "mytcpserver.h"
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyTcpServer myserv;
    qDebug() << "Доступные драйверы баз данных:" << QSqlDatabase::drivers();
    return a.exec();


}

