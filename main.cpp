#include<QApplication>
#include"websocket_server.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SuperContinentServer *sc_server = new SuperContinentServer();

    return app.exec();
}
