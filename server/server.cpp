#include "server.h"
#include "database.h"

#include <QHostAddress>
#include <QDebug>

Server::Server(Database* db)
{
    database = db;
}


bool Server::start(quint16 port)
{
    if (!tcpServer.listen(QHostAddress::Any, port))
        return false;

    if (!httpServer.bind(&tcpServer))
        return false;

    qDebug() << "Server running on" << port;

    return true;
}