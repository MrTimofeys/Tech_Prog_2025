/********************************************************************************
** Form generated from reading UI file 'homewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEWINDOW_H
#define UI_HOMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_welcome;
    QGroupBox *groupBox_input;
    QFormLayout *formLayout;
    QLabel *label_function;
    QComboBox *comboBox_function;
    QLabel *label_x0;
    QLineEdit *lineEdit_x0;
    QLabel *label_tolerance;
    QLineEdit *lineEdit_tolerance;
    QLabel *label_maxIter;
    QLineEdit *lineEdit_maxIter;
    QPushButton *pushButton_solve;
    QGroupBox *groupBox_result;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_result;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HomeWindow)
    {
        if (HomeWindow->objectName().isEmpty())
            HomeWindow->setObjectName("HomeWindow");
        HomeWindow->resize(800, 600);
        centralwidget = new QWidget(HomeWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        label_welcome = new QLabel(centralwidget);
        label_welcome->setObjectName("label_welcome");
        label_welcome->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_welcome);

        groupBox_input = new QGroupBox(centralwidget);
        groupBox_input->setObjectName("groupBox_input");
        formLayout = new QFormLayout(groupBox_input);
        formLayout->setObjectName("formLayout");
        label_function = new QLabel(groupBox_input);
        label_function->setObjectName("label_function");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_function);

        comboBox_function = new QComboBox(groupBox_input);
        comboBox_function->addItem(QString());
        comboBox_function->addItem(QString());
        comboBox_function->addItem(QString());
        comboBox_function->setObjectName("comboBox_function");

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBox_function);

        label_x0 = new QLabel(groupBox_input);
        label_x0->setObjectName("label_x0");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_x0);

        lineEdit_x0 = new QLineEdit(groupBox_input);
        lineEdit_x0->setObjectName("lineEdit_x0");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_x0);

        label_tolerance = new QLabel(groupBox_input);
        label_tolerance->setObjectName("label_tolerance");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_tolerance);

        lineEdit_tolerance = new QLineEdit(groupBox_input);
        lineEdit_tolerance->setObjectName("lineEdit_tolerance");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_tolerance);

        label_maxIter = new QLabel(groupBox_input);
        label_maxIter->setObjectName("label_maxIter");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_maxIter);

        lineEdit_maxIter = new QLineEdit(groupBox_input);
        lineEdit_maxIter->setObjectName("lineEdit_maxIter");

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_maxIter);


        verticalLayout->addWidget(groupBox_input);

        pushButton_solve = new QPushButton(centralwidget);
        pushButton_solve->setObjectName("pushButton_solve");

        verticalLayout->addWidget(pushButton_solve);

        groupBox_result = new QGroupBox(centralwidget);
        groupBox_result->setObjectName("groupBox_result");
        verticalLayout_2 = new QVBoxLayout(groupBox_result);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_result = new QLabel(groupBox_result);
        label_result->setObjectName("label_result");
        label_result->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_result);


        verticalLayout->addWidget(groupBox_result);

        HomeWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HomeWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        HomeWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(HomeWindow);
        statusbar->setObjectName("statusbar");
        HomeWindow->setStatusBar(statusbar);

        retranslateUi(HomeWindow);

        QMetaObject::connectSlotsByName(HomeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HomeWindow)
    {
        HomeWindow->setWindowTitle(QCoreApplication::translate("HomeWindow", "\320\240\320\265\321\210\320\265\320\275\320\270\320\265 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\271", nullptr));
        label_welcome->setText(QCoreApplication::translate("HomeWindow", "\320\240\320\265\321\210\320\265\320\275\320\270\320\265 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\321\217 \320\274\320\265\321\202\320\276\320\264\320\276\320\274 \320\270\321\202\320\265\321\200\320\260\321\206\320\270\320\271", nullptr));
        groupBox_input->setTitle(QCoreApplication::translate("HomeWindow", "\320\222\321\205\320\276\320\264\320\275\321\213\320\265 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));
        label_function->setText(QCoreApplication::translate("HomeWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\204\321\203\320\275\320\272\321\206\320\270\321\216:", nullptr));
        comboBox_function->setItemText(0, QCoreApplication::translate("HomeWindow", "exp(-x)", nullptr));
        comboBox_function->setItemText(1, QCoreApplication::translate("HomeWindow", "(x\302\262 + 6)/5", nullptr));
        comboBox_function->setItemText(2, QCoreApplication::translate("HomeWindow", "0.5 * cos(x)", nullptr));

        label_x0->setText(QCoreApplication::translate("HomeWindow", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\276\320\265 \320\277\321\200\320\270\320\261\320\273\320\270\320\266\320\265\320\275\320\270\320\265 (x0):", nullptr));
        label_tolerance->setText(QCoreApplication::translate("HomeWindow", "\320\242\320\276\321\207\320\275\320\276\321\201\321\202\321\214:", nullptr));
        label_maxIter->setText(QCoreApplication::translate("HomeWindow", "\320\234\320\260\320\272\321\201. \321\207\320\270\321\201\320\273\320\276 \320\270\321\202\320\265\321\200\320\260\321\206\320\270\320\271:", nullptr));
        pushButton_solve->setText(QCoreApplication::translate("HomeWindow", "\320\240\320\265\321\210\320\270\321\202\321\214 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\265", nullptr));
        groupBox_result->setTitle(QCoreApplication::translate("HomeWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
        label_result->setText(QCoreApplication::translate("HomeWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202 \320\261\321\203\320\264\320\265\321\202 \320\276\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275 \320\267\320\264\320\265\321\201\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HomeWindow: public Ui_HomeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEWINDOW_H
