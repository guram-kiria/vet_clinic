#include "database.h"

#include <QDebug>

Database::Database() {}

bool Database::connect()
{
    qDebug() << "connecting to the database";

    db = QSqlDatabase::addDatabase ("QPSQL");

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

void Database::testQuery()
{
    QSqlQuery query;

    query.exec(
        "CREATE TABLE IF NOT EXISTS patients ("
        "id SERIAL PRIMARY KEY,"
        "name TEXT,"
        "species TEXT"
        ")"
    );

    query.exec(
        "INSERT INTO patients(name, species)"
        "VALUES('Buddy', 'dog')"
    );

    while(query.next()){
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString species = query.value("species").toString();

        qDebug() << id << name << species;
    }
}

