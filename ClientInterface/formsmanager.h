#ifndef FORMSMANAGER_H
#define FORMSMANAGER_H

#include <QMainWindow>
#include "authregform.h"
#include "mainwindow.h"

class FormsManager : public QMainWindow
{
    Q_OBJECT

public:
    FormsManager(QWidget *parent = nullptr);
    ~FormsManager();

private:
    AuthRegForm *curr_auth;
    MainWindow *main_form;
};
#endif // FORMSMANAGER_H
