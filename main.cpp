#include <QApplication>
#include <QThread>

#include"websocket_server.h"
#include"game_state.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SCServerPtr scServer(new SuperContinentServer());
    GameStatePtr gsPtr(new GameState(10));

    QObject::connect(scServer.get(), &SuperContinentServer::changeStatus, gsPtr.get(), &GameState::updateStatus);

    return app.exec();
}
