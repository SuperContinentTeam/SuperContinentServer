#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include<QObject>
#include<QWebSocketServer>
#include<QWebSocket>
#include<QRandomGenerator>

typedef std::shared_ptr<QWebSocketServer> QWSServerPtr;
typedef std::shared_ptr<QWebSocket> QWSptr;

class SuperContinentServer: public QObject
{
    Q_OBJECT

    QWSServerPtr qwsServerPtr;
    QList<QWSptr> clients;
    uint16_t port;

    uint16_t gen_rand_port()
    {
        uint16_t result = static_cast<uint16_t>(QRandomGenerator::global()->bounded(50000, 65536));
        return result;
    }

public:
    SuperContinentServer():
        qwsServerPtr(new QWebSocketServer(QString("SuperContinentServer"), QWebSocketServer::NonSecureMode))
    {
        bool connect_success = false;
        while(!connect_success)
        {
            this->port = this->gen_rand_port();
            connect_success = this->qwsServerPtr->listen(QHostAddress::Any, this->port);
        }

    }

    QString print_connect()
    {
        QString address = this->qwsServerPtr->serverAddress().toString();
        return QString("%1:%2").arg(address).arg(this->port);
    }
};

#endif // WEBSOCKET_SERVER_H
