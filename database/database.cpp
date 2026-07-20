#include "database.h"

#include <QDebug>
#include <qdatetime.h>
#include <quuid.h>

Database::Database() {

    db = QSqlDatabase::addDatabase("QPSQL", "vet_connection");
}

bool Database::connect()
{
    qDebug() << "connecting to the database";

    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setDatabaseName("vet_clinic");
    db.setUserName("postgres");
    db.setPassword("CopperB");

    if(!db.open()){
        qDebug() << "Database error:";
        qDebug() << db.lastError().text();
        return false;
    }

    qDebug() << "Connected to PostgreSQL";

    return true;
}

QString Database::createSession(int userId)
{
    QString token = QUuid::createUuid().toString();

    QSqlQuery query(db);

    query.prepare(R"(
        INSERT INTO sessions
        (user_id, token, expires_at)
        VALUES
        (:user_id, :token, :expires_at)
    )");

    query.bindValue(":user_id", userId);
    query.bindValue(":token", token);
    query.bindValue(":expires_at",
                    QDateTime::currentDateTime().addDays(30));

    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        return "";
    }

    return token;
}

std::optional<Database::User> Database::getUser(const QString& username)
{
    QSqlQuery query(QSqlDatabase::database("vet_connection"));

    QString sql = QString(
        "SELECT id, username, password_hash, role "
        "FROM users "
        "WHERE username = '%1'"
    ).arg(username);



    if (!query.exec(sql))
        return std::nullopt;

    if (!query.next())
        return std::nullopt;

    User user;

    user.id = query.value(0).toInt();
    user.username = query.value(1).toString();
    user.passwordHash = query.value(2).toString();
    user.role = query.value(3).toString();
    qDebug() << "password hash" << user.passwordHash;

    return user;
}

