#ifndef SERVER_H
#define SERVER_H


#include <QHttpServer>
#include <QTcpServer>

#include "../auth/authservice.h"

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
    std::unique_ptr<AuthService> authService;

    void registerAuthRoutes(QHttpServer& server, AuthService& authService);
};

#endif // SERVER_H
