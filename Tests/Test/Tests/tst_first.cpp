// #include <QCoreApplication>
// #include <QtTest>

// // add necessary includes here
// #include "homewindow.h"


// class first : public QObject
// {
//     Q_OBJECT

// public:
//     first();
//     ~first();

// private slots:
//     void test_case1();
// };

// first::first() {}

// first::~first() {}

// void first::test_case1() {}

// QTEST_MAIN(first)

// #include "tst_first.moc"

#include <QtTest>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "homewindow.h"

class first : public QObject
{
    Q_OBJECT

private slots:
    void test_homewindow_opens();
    void test_homewindow_default_x0();
    void test_homewindow_solver_runs();
};

// Тест 1: Проверка открытия окна
void first::test_homewindow_opens() {
    HomeWindow window;
    window.show();
    QVERIFY(window.isVisible());
}

// Тест 2: Проверка значения по умолчанию
void first::test_homewindow_default_x0() {
    HomeWindow window;
    QLineEdit* x0Input = window.findChild<QLineEdit*>("lineEdit_x0");
    QVERIFY(x0Input != nullptr);
    QCOMPARE(x0Input->text(), QString("0.0"));  // exp(-x) по умолчанию
}

// Тест 3: Проверка выполнения решения
void first::test_homewindow_solver_runs() {
    HomeWindow window;
    window.show();

    // Устанавливаем корректные значения
    window.findChild<QLineEdit*>("lineEdit_x0")->setText("0.5");
    window.findChild<QLineEdit*>("lineEdit_tolerance")->setText("0.0001");
    window.findChild<QLineEdit*>("lineEdit_maxIter")->setText("100");

    // Нажимаем кнопку "Решить"
    QPushButton* solveButton = window.findChild<QPushButton*>("pushButton_solve");
    QVERIFY(solveButton != nullptr);
    QTest::mouseClick(solveButton, Qt::LeftButton);

    // Проверяем, что результат отображён
    QLabel* resultLabel = window.findChild<QLabel*>("label_result");
    QVERIFY(resultLabel != nullptr);
    QVERIFY(resultLabel->text().contains("Решение: x ="));
}

QTEST_MAIN(first)
#include "tst_first.moc"


