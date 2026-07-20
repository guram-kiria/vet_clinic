#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QString>
#include <optional>

class Database
{
public:
    Database();

    bool connect();

    struct User
    {
        int id;
        QString username;
        QString passwordHash;
        QString role;
    };

    std::optional<User> getUser(const QString& username);
    QString createSession(int userId);

private:
    QSqlDatabase db;



};

#endif // DATABASE_H
