#include "authregform.h"
#include "ui_authregform.h"
#include "funcsforclient.h"

AuthRegForm::AuthRegForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AuthRegForm)
{
    ui->setupUi(this);
    change_enter_type(false);
}

AuthRegForm::~AuthRegForm()
{
    delete ui;
}

void AuthRegForm::change_enter_type(bool is_reg)
{
    // Авторизация = false, регистрация = true

    ui->label_password_check->setVisible(is_reg);
    ui->lineEdit_password_reapet->setVisible(is_reg);

    ui->label_email->setVisible(is_reg);
    ui->lineEdit_email->setVisible(is_reg);

    ui->pushButton_reg->setVisible(is_reg);
    ui->pushButton_auth->setVisible(!is_reg);

    ui->pushButton_to_reg->setText(is_reg ? "to Auth" : "to Reg");
    ui->label_header->setText(is_reg ? "Registration" : "Authentication");
}

void AuthRegForm::clear_form()
{
    ui->lineEdit_login->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_password_reapet->clear();
    ui->lineEdit_email->clear();

    // ui->lineEdit_login->setText("");
    // ui->lineEdit_password->setText("");
    // ui->lineEdit_password_reapet->setText("");
    // ui->lineEdit_email->setText("");
}

void AuthRegForm::on_pushButton_to_reg_clicked()
{
    change_enter_type(!ui->label_email->isVisible());
}

void AuthRegForm::on_pushButton_auth_clicked()
{
    if (auth(ui->lineEdit_login->text(), ui->lineEdit_password->text()))
    {
        ui->label_test_status->setText("Authentication completed");

        emit auth_ok(ui->lineEdit_login->text()); // Вызов сигнала
        //this->close();
    }
    else
    {
        ui->label_test_status->setText("Authentication failed");
        clear_form();
    }
}

void AuthRegForm::on_pushButton_reg_clicked()
{
    if (ui->lineEdit_password->text() == ui->lineEdit_password_reapet->text() &&
        reg(ui->lineEdit_login->text(),
            ui->lineEdit_password->text(),
            ui->lineEdit_email->text())
        )
    {
        ui->label_test_status->setText("Registration completed");

        emit auth_ok(ui->lineEdit_login->text()); // Вызов сигнала
        this->close();
    }
    else
    {
        ui->label_test_status->setText("Registration failed");
        clear_form();
    }
}
