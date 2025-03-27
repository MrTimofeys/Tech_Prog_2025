#include "formsmanager.h"

FormsManager::FormsManager(QWidget *parent)
    : QMainWindow(parent)
{
    this->curr_auth = new AuthRegForm();
    this->curr_auth->show();
    //connect(curr_auth, &AuthRegForm::auth_ok, main_form, &MainWindow::slot_show);
}

FormsManager::~FormsManager() {}
