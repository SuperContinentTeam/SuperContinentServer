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

void GameState::updateStatus(quint8 s){
    switch (s) {
    case 1:
        // RUNNING
        this->status = GameState::Status::RUNING;
        break;
    case 2:
        // PAUSE
        this->status = GameState::Status::PAUSE;
        break;
    case 0:
        // END
        this->status = GameState::Status::END;
        break;
    default:
        break;
    }
}

