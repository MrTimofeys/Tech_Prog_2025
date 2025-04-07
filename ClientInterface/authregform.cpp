#include "authregform.h"
#include "ui_authregform.h"
#include "funcsforclient.h"
#include "clientmanager.h"
#include "homewindow.h"
#include <QMessageBox>

AuthRegForm::AuthRegForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AuthRegForm)
{
    ui->setupUi(this);
    change_enter_type(false);
    
    // Подключаемся к сигналам ClientManager
    ClientManager* client = ClientManager::getInstance();
    connect(client, &ClientManager::loginResult, this, &AuthRegForm::handleLoginResult);
    connect(client, &ClientManager::registrationResult, this, &AuthRegForm::handleRegistrationResult);
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
}

void AuthRegForm::on_pushButton_to_reg_clicked()
{
    change_enter_type(!ui->label_email->isVisible());
}

void AuthRegForm::on_pushButton_auth_clicked()
{
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();
    
    if (login.isEmpty() || password.isEmpty()) {
        ui->label_test_status->setText("Please fill in all fields");
        return;
    }
    
    ui->label_test_status->setText("Authenticating...");
    auth(login, password);
}

void AuthRegForm::on_pushButton_reg_clicked()
{
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();
    QString passwordRepeat = ui->lineEdit_password_reapet->text();
    QString email = ui->lineEdit_email->text();
    
    if (login.isEmpty() || password.isEmpty() || email.isEmpty()) {
        ui->label_test_status->setText("Please fill in all fields");
        return;
    }
    
    if (password != passwordRepeat) {
        ui->label_test_status->setText("Passwords do not match");
        return;
    }
    
    ui->label_test_status->setText("Registering...");
    reg(login, password, email);
}

void AuthRegForm::handleLoginResult(bool success, const QString& message)
{
    if (success) {
        ui->label_test_status->setText("Authentication successful");
        HomeWindow *homeWindow = new HomeWindow();
        homeWindow->show();
        this->close();
    } else {
        ui->label_test_status->setText("Authentication failed: " + message);
        clear_form();
    }
}

void AuthRegForm::handleRegistrationResult(bool success, const QString& message)
{
    if (success) {
        ui->label_test_status->setText("Registration successful. Please login.");
        change_enter_type(false); // Переключаемся на форму авторизации
        clear_form();
    } else {
        ui->label_test_status->setText("Registration failed: " + message);
        clear_form();
    }
}
