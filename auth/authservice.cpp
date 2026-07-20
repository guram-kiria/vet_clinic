#include "authservice.h"
#include "../database/database.h"


AuthService::AuthService(Database& db)
    : m_database(db)
{
}

QString AuthService::login(const QString& username,
                           const QString& password)
{
    auto user = m_database.getUser(username);

    ;
    if (!user)
        return "";

    if (user->passwordHash != password)
        return "";

    return m_database.createSession(user->id);
}

bool AuthService::validateToken(const QString& token)
{
    return false;
}