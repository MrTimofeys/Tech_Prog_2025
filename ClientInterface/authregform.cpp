#include "authregform.h"
#include "ui_authregform.h"
#include "funcsforclient.h"
#include "clientmanager.h"
#include "homewindow.h"
#include <QMessageBox>
#include <QTimer>

AuthRegForm::AuthRegForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AuthRegForm)
    , isRequestInProgress(false)
{
    ui->setupUi(this);
    change_enter_type(false);
    showPasswordResetForm(false);
    
    // Подключаемся к сигналам ClientManager
    ClientManager* client = ClientManager::getInstance();
    connect(client, &ClientManager::loginResult, this, &AuthRegForm::handleLoginResult);
    connect(client, &ClientManager::registrationResult, this, &AuthRegForm::handleRegistrationResult);
    connect(client, &ClientManager::verificationCodeResult, this, &AuthRegForm::handleVerificationCodeResult);
    connect(client, &ClientManager::passwordResetResult, this, &AuthRegForm::handlePasswordResetResult);
}

AuthRegForm::~AuthRegForm()
{
    ClientManager* client = ClientManager::getInstance();
    disconnect(client, &ClientManager::loginResult, this, &AuthRegForm::handleLoginResult);
    disconnect(client, &ClientManager::registrationResult, this, &AuthRegForm::handleRegistrationResult);
    disconnect(client, &ClientManager::verificationCodeResult, this, &AuthRegForm::handleVerificationCodeResult);
    disconnect(client, &ClientManager::passwordResetResult, this, &AuthRegForm::handlePasswordResetResult);
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

void AuthRegForm::showPasswordResetForm(bool show)
{
    ui->resetPasswordWidget->setVisible(show);
    ui->formLayoutWidget->setVisible(!show);
    ui->horizontalLayoutWidget->setVisible(!show);
    
    if (show) {
        ui->label_header->setText("Password Reset");
    } else {
        change_enter_type(false);
    }
}

void AuthRegForm::clearPasswordResetForm()
{
    ui->lineEdit_verification_code->clear();
    ui->lineEdit_new_password->clear();
    ui->lineEdit_confirm_new_password->clear();
}

void AuthRegForm::on_pushButton_forgot_password_clicked()
{
    showPasswordResetForm(true);
}

void AuthRegForm::on_pushButton_send_code_clicked()
{
    if (isRequestInProgress) {
        ui->label_test_status->setText("Please wait, code is being sent...");
        return;
    }
    
    QString username = ui->lineEdit_login->text();
    
    if (username.isEmpty()) {
        ui->label_test_status->setText("Please enter your username");
        return;
    }
    
    ClientManager* client = ClientManager::getInstance();
    isRequestInProgress = true;
    client->sendVerificationCode(username);
    ui->label_test_status->setText("Sending verification code...");
    
    // Сбрасываем флаг через небольшую задержку
    QTimer::singleShot(3000, this, [this]() {
        isRequestInProgress = false;
    });
}

void AuthRegForm::on_pushButton_reset_password_clicked()
{
    QString username = ui->lineEdit_login->text();
    QString verificationCode = ui->lineEdit_verification_code->text();
    QString newPassword = ui->lineEdit_new_password->text();
    QString confirmPassword = ui->lineEdit_confirm_new_password->text();
    
    if (username.isEmpty() || verificationCode.isEmpty() || 
        newPassword.isEmpty() || confirmPassword.isEmpty()) {
        ui->label_test_status->setText("Please fill in all fields");
        return;
    }
    
    if (newPassword != confirmPassword) {
        ui->label_test_status->setText("Passwords do not match");
        return;
    }
    
    ClientManager* client = ClientManager::getInstance();
    client->resetPassword(username, verificationCode, newPassword);
    ui->label_test_status->setText("Resetting password...");
}

void AuthRegForm::on_pushButton_cancel_reset_clicked()
{
    ClientManager* client = ClientManager::getInstance();
    client->clearStoredVerificationCode();
    showPasswordResetForm(false);
    clearPasswordResetForm();
}

void AuthRegForm::handleVerificationCodeResult(bool success, const QString& message)
{
    static bool isHandling = false;
    
    if (isHandling) return;
    
    isHandling = true;
    ClientManager* client = ClientManager::getInstance();
    if (success) {
        // ui->label_test_status->setText(message + " Code: " + client->getStoredVerificationCode());
        ui->label_test_status->setText(message);
    } else {
        ui->label_test_status->setText(message);
    }
    isRequestInProgress = false;
    isHandling = false;
}

void AuthRegForm::handlePasswordResetResult(bool success, const QString& message)
{
    ui->label_test_status->setText(message);
    if (success) {
        showPasswordResetForm(false);
        clearPasswordResetForm();
    }
}
