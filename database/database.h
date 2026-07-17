#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


class Database
{
public:
    Database();

    bool connect();
    void testQuery();

private:
    QSqlDatabase db;

};

#endif // DATABASE_H
