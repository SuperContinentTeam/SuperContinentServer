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

    // if(!message.compare("#start")) {
    //     emit this->changeStatus(1);
    // }else if(!message.compare("#pause")) {
    //     emit this->changeStatus(2);
    // }else if(!message.compare("#end")) {
    //     emit this->changeStatus(0);
    // }
}

void SuperContinentServer::socketDisconnected()
{
    QString peer = this->get_peer(qobject_cast<QWebSocket*>(sender()));

    qInfo() << QString("Client(%1) disconnect").arg(peer);

    this->clientsMap.remove(peer);
}
