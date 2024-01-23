#include"game_state.h"

GameState::GameState(quint8 wSize):QObject(nullptr)
{
    this->worldSize = wSize;

    this->gsThread = new QThread(this);
    this->moveToThread(this->gsThread);
    this->gsThread->start();
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
    while(true) {
        if(this->status == GameState::Status::END) break;
        if(this->status == GameState::Status::RUNING) {
            this->next_state();
            this->show_current_status();
        }

        QThread::sleep(1);
    }
}

void GameState::updateStatus(quint8 s)
{
    switch (s) {
    case 1:
        // RUNNING
        this->status = GameState::Status::RUNING;
        break;
    case 2:
        // PAUSE
        this->status = GameState::Status::PAUSE;
        break;
    default:
        // END
        this->status = GameState::Status::END;
        break;
    }


}

