#include "state_worker.h"

StateWorker::StateWorker()
    :QThread(nullptr)
{

}

void StateWorker::updateGameStatus(quint8 s)
{
        switch (s) {
        case 1:
            // RUNNING
            this->gsPtr->status = GameState::Status::RUNING;
            break;
        case 2:
            // PAUSE
            this->gsPtr->status = GameState::Status::PAUSE;
            break;
        default:
            // END
            this->gsPtr->status = GameState::Status::END;
            break;
        }
}
