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

signals:
    void auth_ok(QString);

private:
    Ui::AuthRegForm *ui;

    void change_enter_type(bool);
    void clear_form();
};

#endif // AUTHREGFORM_H
