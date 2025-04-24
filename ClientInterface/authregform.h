#ifndef AUTHREGFORM_H
#define AUTHREGFORM_H

#include <QDialog>

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

    void on_pushButton_forgot_password_clicked();
    void on_pushButton_send_code_clicked();
    void on_pushButton_reset_password_clicked();
    void on_pushButton_cancel_reset_clicked();
    void handlePasswordResetResult(bool success, const QString& message);
    void handleVerificationCodeResult(bool success, const QString& message);

signals:
    void auth_ok(QString);

private:
    Ui::AuthRegForm *ui;

    void change_enter_type(bool);
    void clear_form();

    void showPasswordResetForm(bool show);
    void clearPasswordResetForm();
};

#endif // AUTHREGFORM_H
