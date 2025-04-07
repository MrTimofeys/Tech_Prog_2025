#ifndef FUNCSFORCLIENT_H
#define FUNCSFORCLIENT_H

#include <QString>
#include <QObject>
#include <QDebug>

bool auth(QString login, QString password);
bool reg(QString login, QString password, QString email);

#endif // FUNCSFORCLIENT_H
