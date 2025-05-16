#include "formsmanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FormsManager w;
    //w.show();
    return a.exec();
}

// #include <QtTest>
// #include "test_minimal.cpp"  // или любой другой тест-файл

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);  // если твой тест требует GUI
//     MinimalTest test;
//     return QTest::qExec(&test, argc, argv);
// }
