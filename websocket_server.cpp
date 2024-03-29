
#include"websocket_server.h"

SuperContinentServer::SuperContinentServer(quint16 port):        qwsServerPtr(new QWebSocketServer(QString("SuperContinentServer"), QWebSocketServer::NonSecureMode)),
    port(port)
{
    if(this->qwsServerPtr->listen(QHostAddress(QHostAddress::AnyIPv4), this->port)) {
        connect(qwsServerPtr.get(), &QWebSocketServer::newConnection, this, &SuperContinentServer::onConnection);

        qInfo() << QString("Listening on 0.0.0.0:%1").arg(this->port);
    } else {
        qInfo() << "Listening failed!";
    }
}

void SuperContinentServer::onConnection()
{
    QWSptr sock(this->qwsServerPtr->nextPendingConnection());
    QString peerAddressHost = QString("%1:%2").arg(sock->peerAddress().toString(), QString::number(sock->peerPort()));

    qInfo() << QString("New connection: %1").arg(peerAddressHost);

    connect(sock.get(), &QWebSocket::textMessageReceived, this, &SuperContinentServer::processTextMessage);
    connect(sock.get(), &QWebSocket::disconnected, this, &SuperContinentServer::socketDisconnected);

    this->clientsMap.insert(peerAddressHost, sock);
}

void SuperContinentServer::processTextMessage(const QString &message)
{
    QString peer = this->get_peer(qobject_cast<QWebSocket*>(sender()));

    emit this->sendTextCommand(peer, message);
}

void SuperContinentServer::socketDisconnected()
{
    QString peer = this->get_peer(qobject_cast<QWebSocket*>(sender()));

    qInfo() << QString("Client(%1) disconnect").arg(peer);

    this->clientsMap.remove(peer);
}

void SuperContinentServer::boardcast(const QString &message)
{
    qDebug() << "收到信号, 准备广播消息";
    for (auto iterator = this->clientsMap.begin(); iterator != this->clientsMap.end(); iterator++) {
        QWSptr p = iterator.value();
        p->sendTextMessage(message);
    }
}

void SuperContinentServer::sendToPeer(const QString &peer, const QString &message)
{
    QWSptr p = this->clientsMap.value(peer, nullptr);
    if (p != nullptr) {
        p->sendTextMessage(message);
    }
}
