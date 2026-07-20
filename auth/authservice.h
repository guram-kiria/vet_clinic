#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <QString>

class Database;

class AuthService
{
public:
    explicit AuthService(Database& db);

    QString login(const QString& username,
                  const QString& password);

    bool validateToken(const QString& token);

private:
    Database& m_database;
};

#endif // AUTHSERVICE_H
