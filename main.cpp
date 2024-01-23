#include <QApplication>
#include <QThread>

#include"websocket_server.h"
#include"game_state.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SCServerPtr scServer(new SuperContinentServer());
    GameStatePtr gsPtr(new GameState(10));

    QObject::connect(scServer.get(), &SuperContinentServer::readyStart, gsPtr.get(), &GameState::run);

    QThread *gsThread = new QThread;
    gsPtr->moveToThread(gsThread);
    gsThread->start();

    return app.exec();
}
