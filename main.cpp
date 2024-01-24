#include <QApplication>
#include <QThread>

#include"websocket_server.h"
#include"game_state.h"
#include"state_worker.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /* 以后用UI来设置的变量 */
    quint16 mPort = 65531;
    quint8 mWorldSize = 10;

    SCServerPtr scServer(new SuperContinentServer(mPort));
    GameStatePtr gsPtr(new GameState(mWorldSize));

    StateWorker *sw = new StateWorker();
    sw->setGameStatePtr(gsPtr);

    QObject::connect(scServer.get(), &SuperContinentServer::sendTextCommand, sw, &StateWorker::textCommandExecuater);

    sw->start();

    return app.exec();
}
