#include <QCoreApplication>

#include <QHttpServer>
#include <QTcpServer>
#include <QHostAddress>

#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

#include "database.h"
#include "server.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Database db;
    db.connect();

    Server server(&db);
    server.start(8080);


    return app.exec();
}
