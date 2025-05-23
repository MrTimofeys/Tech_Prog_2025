#include "testmytcpserver.h"

void TestMyTcpServer::initTestCase()
{
    server = new MyTcpServer(nullptr, true);

    QSqlQuery query(QSqlDatabase::database());
    query.exec("DELETE FROM users");
}


void TestMyTcpServer::cleanupTestCase() {
    delete server;
}

void TestMyTcpServer::testRegisterUser() {
    QVERIFY(server->registerUser("user1", "pass123", "user1@example.com"));
    QVERIFY(!server->registerUser("user1", "pass123", "user1@example.com"));
}

void TestMyTcpServer::testAuthenticateUser() {
    server->registerUser("user2", "mypassword", "user2@example.com");
    QVERIFY(server->authenticateUser("user2", "mypassword"));
    QVERIFY(!server->authenticateUser("user2", "wrongpass"));
}

void TestMyTcpServer::testHashPasswordConsistency() {
    QString hash1 = server->hashPassword("password");
    QString hash2 = server->hashPassword("password");
    QCOMPARE(hash1, hash2);
}

void TestMyTcpServer::testGenerateRandomCodeLength() {
    QString code = server->generateRandomCode(6);
    QCOMPARE(code.length(), 6);
}

void TestMyTcpServer::testGenerateRandomCodeUniqueness() {
    QString code1 = server->generateRandomCode(6);
    QString code2 = server->generateRandomCode(6);
    QVERIFY(code1 != code2);
}
void TestMyTcpServer::testFailedAuthentication() {
    server->registerUser("user3", "correctpass", "user3@example.com");
    QVERIFY(!server->authenticateUser("user3", "wrongpass"));
}

void TestMyTcpServer::testDuplicateUsernameRegistration() {
    bool firstTry = server->registerUser("user4", "pass1", "user4@example.com");
    bool secondTry = server->registerUser("user4", "pass2", "user4duplicate@example.com");
    QVERIFY(firstTry);
    QVERIFY(!secondTry);
}

void TestMyTcpServer::testMathFunc() {
    double result = MyTcpServer::mathFunc(0.0);
    QCOMPARE(result, 1.0);
}

void TestMyTcpServer::testSolveEquation() {
    QString functionName = "phi_quadratic";
    double x0 = 1.0;
    double tolerance = 1e-6;
    int maxIterations = 100;

    double result = equationSolver::solveIterationMethod(functionName, x0, tolerance, maxIterations);

    qDebug() << "Результат:" << result;
    QVERIFY(!std::isnan(result));
    QVERIFY(result >= 1.5 && result <= 2.6);
}


