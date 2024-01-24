#include "state_worker.h"

StateWorker::StateWorker():QThread(nullptr){}

void StateWorker::setGameStatePtr(GameStatePtr gsPtr) {
    this->gsPtr = gsPtr;
}


void StateWorker::updateGameStatus(quint8 s)
{
    this->gsPtr->updateStatus(s);
}
