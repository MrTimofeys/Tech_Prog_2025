/********************************************************************************
** Form generated from reading UI file 'authregform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHREGFORM_H
#define UI_AUTHREGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthRegForm
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_reg;
    QPushButton *pushButton_auth;
    QPushButton *pushButton_to_reg;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_login;
    QLabel *label_password;
    QLabel *label_password_check;
    QLabel *label_email;
    QLineEdit *lineEdit_password;
    QLineEdit *lineEdit_email;
    QLineEdit *lineEdit_password_reapet;
    QLineEdit *lineEdit_login;
    QLabel *label_header;
    QLabel *label_test_status;

    void setupUi(QDialog *AuthRegForm)
    {
        if (AuthRegForm->objectName().isEmpty())
            AuthRegForm->setObjectName("AuthRegForm");
        AuthRegForm->resize(400, 300);
        horizontalLayoutWidget = new QWidget(AuthRegForm);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(20, 210, 351, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_reg = new QPushButton(horizontalLayoutWidget);
        pushButton_reg->setObjectName("pushButton_reg");

        horizontalLayout->addWidget(pushButton_reg);

        pushButton_auth = new QPushButton(horizontalLayoutWidget);
        pushButton_auth->setObjectName("pushButton_auth");

        horizontalLayout->addWidget(pushButton_auth);

        pushButton_to_reg = new QPushButton(horizontalLayoutWidget);
        pushButton_to_reg->setObjectName("pushButton_to_reg");

        horizontalLayout->addWidget(pushButton_to_reg);

        formLayoutWidget = new QWidget(AuthRegForm);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(20, 60, 351, 102));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_login = new QLabel(formLayoutWidget);
        label_login->setObjectName("label_login");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_login);

        label_password = new QLabel(formLayoutWidget);
        label_password->setObjectName("label_password");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_password);

        label_password_check = new QLabel(formLayoutWidget);
        label_password_check->setObjectName("label_password_check");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_password_check);

        label_email = new QLabel(formLayoutWidget);
        label_email->setObjectName("label_email");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_email);

        lineEdit_password = new QLineEdit(formLayoutWidget);
        lineEdit_password->setObjectName("lineEdit_password");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_password);

        lineEdit_email = new QLineEdit(formLayoutWidget);
        lineEdit_email->setObjectName("lineEdit_email");

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_email);

        lineEdit_password_reapet = new QLineEdit(formLayoutWidget);
        lineEdit_password_reapet->setObjectName("lineEdit_password_reapet");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_password_reapet);

        lineEdit_login = new QLineEdit(formLayoutWidget);
        lineEdit_login->setObjectName("lineEdit_login");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_login);

        label_header = new QLabel(AuthRegForm);
        label_header->setObjectName("label_header");
        label_header->setGeometry(QRect(20, 10, 141, 21));
        label_test_status = new QLabel(AuthRegForm);
        label_test_status->setObjectName("label_test_status");
        label_test_status->setGeometry(QRect(20, 170, 351, 31));

        retranslateUi(AuthRegForm);

        QMetaObject::connectSlotsByName(AuthRegForm);
    } // setupUi

    void retranslateUi(QDialog *AuthRegForm)
    {
        AuthRegForm->setWindowTitle(QCoreApplication::translate("AuthRegForm", "Dialog", nullptr));
        pushButton_reg->setText(QCoreApplication::translate("AuthRegForm", "Reg", nullptr));
        pushButton_auth->setText(QCoreApplication::translate("AuthRegForm", "Auth", nullptr));
        pushButton_to_reg->setText(QCoreApplication::translate("AuthRegForm", "to Reg", nullptr));
        label_login->setText(QCoreApplication::translate("AuthRegForm", "Login", nullptr));
        label_password->setText(QCoreApplication::translate("AuthRegForm", "Password", nullptr));
        label_password_check->setText(QCoreApplication::translate("AuthRegForm", "Password repeat", nullptr));
        label_email->setText(QCoreApplication::translate("AuthRegForm", "Email", nullptr));
        label_header->setText(QCoreApplication::translate("AuthRegForm", "Window", nullptr));
        label_test_status->setText(QCoreApplication::translate("AuthRegForm", "Status", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AuthRegForm: public Ui_AuthRegForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHREGFORM_H
