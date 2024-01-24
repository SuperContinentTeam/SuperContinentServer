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
    quint16 port;

public:
    SuperContinentServer(quint16 port);

    QString get_peer(QWebSocket* ws){
        return QString("%1:%2").arg(ws->peerAddress().toString(), QString::number(ws->peerPort()));
    }

private slots:
    void onConnection();

    void processTextMessage(const QString& message);

    void socketDisconnected();

signals:
    void sendTextCommand(QString, QString);
};


typedef std::shared_ptr<SuperContinentServer> SCServerPtr;

#endif // WEBSOCKET_SERVER_H
