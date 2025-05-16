#include <QCoreApplication>
#include <QtTest>

// add necessary includes here
#include "homewindow.h"


class first : public QObject
{
    Q_OBJECT

public:
    first();
    ~first();

private slots:
    void test_case1();
};

first::first() {}

first::~first() {}

void first::test_case1() {}

QTEST_MAIN(first)

#include "tst_first.moc"
