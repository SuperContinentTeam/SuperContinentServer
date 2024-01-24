#include <QApplication>
#include <QThread>

#include"websocket_server.h"
#include"game_state.h"
#include"state_worker.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SCServerPtr scServer(new SuperContinentServer());
    GameStatePtr gsPtr(new GameState(10));

    StateWorker *sw = new StateWorker();
    sw->setGameStatePtr(gsPtr);

    QObject::connect(scServer.get(), &SuperContinentServer::changeStatus, sw, &StateWorker::updateGameStatus);

    sw->start();

    return app.exec();
}
