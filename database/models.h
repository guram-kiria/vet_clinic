#ifndef MODELS_H
#define MODELS_H

#include <QString>
#include <QDateTime>

struct Session
{
    int id;
    int userId;
    QString token;
    QDateTime expiresAt;
};

#endif // MODELS_H
