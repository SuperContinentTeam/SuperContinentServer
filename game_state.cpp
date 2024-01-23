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

void GameState::show_current_status(){
    qInfo() << QString("Current tick: %1").arg(this->tick);
}

void GameState::run() {
    while(!this->isPause) {
        if(this->isEnd) break;

        this->next_state();
        this->show_current_status();
        QThread::msleep(1000);
    }
}

