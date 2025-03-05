#include "funcsforclient.h"
#include <QString>

bool auth(QString login, QString password)
{
    // TODO: Запрос на сервер
    if (login == "admin" && password == "admin") {
        return true;
    } else {
        return false;
    }
}

bool reg(QString login, QString password, QString email)
{
    // TODO: Логика регистарции + авторизация сразу после
    if (login != "admin" || password != "admin")
        return true;
    else
        return false;
}
