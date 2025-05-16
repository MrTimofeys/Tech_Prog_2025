#include <QtTest>
#include "homewindow.h"

class TestHomeWindow : public QObject {
    Q_OBJECT

private slots:
    void test_window_opens();
};

void TestHomeWindow::test_window_opens() {
    HomeWindow window;
    window.show();
    QVERIFY(window.isVisible());
}

QTEST_MAIN(TestHomeWindow)
#include "test_homewindow.moc"
