#include"game_state.h"

GameState::GameState(quint8 wSize):QObject(nullptr)
{
    this->worldSize = wSize;
}

GameState::~GameState(){}

void GameState::next_state()
{
    this->tick++;
}

void GameState::display(){
    qInfo() << QString("Current tick: %1").arg(this->tick);
}

bool GameState::playerJoin(QString peer, PlayerPtr player)
{
    if (this->playerMap.size() == this->maxPlayer)
        return false;

    this->playerMap.insert(peer, player);
    return true;
}


void GameState::playerLeave(QString peer)
{
    this->playerMap.remove(peer);
}
