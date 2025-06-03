#ifndef TESTMYTCPSERVER_H
#define TESTMYTCPSERVER_H

#include <QObject>
#include <QtTest>
#include "../Server/mytcpserver.h"

class TestMyTcpServer : public QObject
{
    Q_OBJECT

private:
    MyTcpServer* server;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testRegisterUser();
    void testAuthenticateUser();
    void testHashPasswordConsistency();
    void testGenerateRandomCodeLength();
    void testGenerateRandomCodeUniqueness();
    void testFailedAuthentication();
    void testDuplicateUsernameRegistration();
    void testMathFunc();
    void testSolveEquation();
};

#endif // TESTMYTCPSERVER_H
