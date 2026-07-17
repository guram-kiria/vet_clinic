#ifndef SERVER_H
#define SERVER_H


#include <QHttpServer>
#include <QTcpServer>

class Database;

class Server
{
public:
    Server(Database* db);

    bool start(quint16 port);

private:
    QHttpServer httpServer;
    QTcpServer tcpServer;

    Database* database;
};

#endif // SERVER_H
