#include "server.h"
#include "../database/database.h"

#include <QHostAddress>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

Server::Server(Database* db)
{
    database = db;

    authService = std::make_unique<AuthService>(*database);


    registerAuthRoutes(httpServer, *authService);
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

void Server::registerAuthRoutes(QHttpServer &server, AuthService &authService)
{

    qDebug() << "auth route registered";
    server.route("/login",
                QHttpServerRequest::Method::Post,
                [&](const QHttpServerRequest& request)
    {
        auto json = QJsonDocument::fromJson(request.body()).object();

        QString username = json["username"].toString();
        QString password = json["password"].toString();

        QString token = authService.login(username, password);
        qDebug() << "token" << token;

        if (token.isEmpty())
            return QHttpServerResponse(QHttpServerResponder::StatusCode::Unauthorized);

        QJsonObject response;
        response["token"] = token;

        return QHttpServerResponse("application/json",QJsonDocument(response).toJson());
    });
}

