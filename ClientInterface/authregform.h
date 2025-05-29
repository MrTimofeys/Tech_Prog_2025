#ifndef AUTHREGFORM_H
#define AUTHREGFORM_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class AuthRegForm;
}

class AuthRegForm : public QDialog
{
    Q_OBJECT

public:
    explicit AuthRegForm(QWidget *parent = nullptr);
    ~AuthRegForm();

private slots:
    void on_pushButton_to_reg_clicked();

    void on_pushButton_auth_clicked();

    void on_pushButton_reg_clicked();

    void handleLoginResult(bool success, const QString& message);
    void handleRegistrationResult(bool success, const QString& message);
    void handleVerificationCodeResult(bool success, const QString& message);
    void handlePasswordResetResult(bool success, const QString& message);
    void handleConnectionStatus(bool connected);

    void on_pushButton_forgot_password_clicked();
    void on_pushButton_send_code_clicked();
    void on_pushButton_verify_code_clicked();
    void on_pushButton_reset_password_clicked();
    void on_pushButton_cancel_reset_clicked();

signals:
    void auth_ok(QString);

private:
    Ui::AuthRegForm *ui;
    bool isRequestInProgress;
    void change_enter_type(bool is_reg);
    void clear_form();

    void showPasswordResetForm(bool show);
    void showNewPasswordFields(bool show);
    void clearPasswordResetForm();
    void auth(const QString& login, const QString& password);
    void reg(const QString& login, const QString& password, const QString& email);
};

#endif // AUTHREGFORM_H
