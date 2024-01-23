#include"websocket_server.h"

//int main(int argc, char *argv[])
int main()
{
    SuperContinentServer *sc_server = new SuperContinentServer();
    qDebug() << sc_server->print_connect();
    return 0;
}
