#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include<QObject>
#include<QWebSocketServer>
#include<QWebSocket>
#include<QRandomGenerator>

typedef std::shared_ptr<QWebSocketServer> QWSServerPtr;
typedef std::shared_ptr<QWebSocket> QWSptr;

class SuperContinentServer: public QObject{
    Q_OBJECT

    QWSServerPtr qwsServerPtr;
    QMap<QString, QWSptr> clientsMap;
    uint16_t port;

    uint16_t gen_rand_port(){
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
            connect_success = this->qwsServerPtr->listen(QHostAddress::AnyIPv4, this->port);
        }
        qInfo() << QString("Listening on %1").arg(this->print_connect());

        connect(qwsServerPtr.get(), SIGNAL(newConnection()), this, SLOT(on_connection()));
    }

    QString print_connect(){
        QString address = this->qwsServerPtr->serverAddress().toString();
        return QString("%1:%2").arg(address).arg(this->port);
    }

    QString client_address(QWSptr ws){
        return QString("%1:%2").arg(ws->peerAddress().toString()).arg(ws->peerPort());
    }

private slots:
    void on_connection(){
        QWSptr sock(this->qwsServerPtr->nextPendingConnection());
        QString peerAddressHost = this->client_address(sock);

        qInfo() << QString("New connection: %1").arg(peerAddressHost);

        connect(sock.get(), SIGNAL(textMessageReceived(QString)),this, SLOT(processTextMessage(QString)));
        connect(sock.get(), SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

        this->clientsMap.insert(peerAddressHost, sock);
    }

    void processTextMessage(const QString& message){
        QWebSocket *c = qobject_cast<QWebSocket*>(sender());
        QString peer = QString("%1:%2").arg(c->peerAddress().toString(), c->peerPort());
        QString msg = QString("%1 said: %2").arg(peer, message);
        qInfo() << msg;
    }

    void socketDisconnected(){
        QWebSocket *c = qobject_cast<QWebSocket*>(sender());
        QString peer = QString("%1:%2").arg(c->peerAddress().toString(), c->peerPort());
        qInfo() << QString("Client(%1) disconnect").arg(peer);

        this->clientsMap.remove(peer);
    }

signals:
    void readyStart();
};


typedef std::shared_ptr<SuperContinentServer> SCServerPtr;

#endif // WEBSOCKET_SERVER_H
