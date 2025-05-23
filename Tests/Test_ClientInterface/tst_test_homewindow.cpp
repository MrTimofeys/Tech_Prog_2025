#include <QtTest>

// add necessary includes here

class test_homewindow : public QObject
{
    Q_OBJECT

public:
    test_homewindow();
    ~test_homewindow();

private slots:
    void test_case1();
};

test_homewindow::test_homewindow() {}

test_homewindow::~test_homewindow() {}

void test_homewindow::test_case1() {}

QTEST_APPLESS_MAIN(test_homewindow)

#include "tst_test_homewindow.moc"
