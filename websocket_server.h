#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include<QObject>
#include<QWebSocketServer>
#include<QWebSocket>

typedef std::shared_ptr<QWebSocketServer> QWSServerPtr;
typedef std::shared_ptr<QWebSocket> QWSptr;

class SuperContinentServer: public QObject{
    Q_OBJECT

    QWSServerPtr qwsServerPtr;
    QMap<QString, QWSptr> clientsMap;
    QString host;
    quint16 port;

public:
    SuperContinentServer(QString host=QString("0.0.0.0"), quint16 port=65530):
        qwsServerPtr(new QWebSocketServer(QString("SuperContinentServer"), QWebSocketServer::NonSecureMode)),
        host(host), port(port)
    {
        this->qwsServerPtr->listen(QHostAddress(this->host), this->port);
        qInfo() << QString("Listening on 0.0.0.0:%1").arg(this->port);
        connect(qwsServerPtr.get(), &QWebSocketServer::newConnection, this, &SuperContinentServer::on_connection);
    }

    QString get_peer(QWebSocket* ws){
        return QString("%1:%2").arg(ws->peerAddress().toString(), QString::number(ws->peerPort()));
    }

private slots:
    void on_connection(){
        QWSptr sock(this->qwsServerPtr->nextPendingConnection());
        QString peerAddressHost = QString("%1:%2").arg(sock->peerAddress().toString(), QString::number(sock->peerPort()));

        qInfo() << QString("New connection: %1").arg(peerAddressHost);

        connect(sock.get(), &QWebSocket::textMessageReceived, this, &SuperContinentServer::processTextMessage);
        connect(sock.get(), &QWebSocket::disconnected, this, &SuperContinentServer::socketDisconnected);

        this->clientsMap.insert(peerAddressHost, sock);
    }

    void processTextMessage(const QString& message){
        QString peer = this->get_peer(qobject_cast<QWebSocket*>(sender()));
        QString msg = QString("%1 said: %2").arg(peer, message);

        if(msg == "start") {
            emit changeStatus(1);
        }else{
            emit changeStatus(2);
        }

        qInfo() << msg;
    }

    void socketDisconnected(){
        QString peer = this->get_peer(qobject_cast<QWebSocket*>(sender()));

        qInfo() << QString("Client(%1) disconnect").arg(peer);

        this->clientsMap.remove(peer);
    }

signals:
    void changeStatus(quint8);
};


typedef std::shared_ptr<SuperContinentServer> SCServerPtr;

#endif // WEBSOCKET_SERVER_H
