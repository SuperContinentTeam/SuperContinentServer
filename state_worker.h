#ifndef STATE_WORKER_H
#define STATE_WORKER_H

#include <QObject>
#include <QThread>
#include <QJsonDocument>

#include "game_state.h"

class StateWorker : public QThread
{
    GameStatePtr gsPtr;
public:
    explicit StateWorker();

    void setGameStatePtr(GameStatePtr gsPtr);

    void run() override {
        qDebug() << "状态机线程已启动";
        while (true) {
            if(this->gsPtr->status == GameState::Status::END) break;
            if(this->gsPtr->status == GameState::Status::RUNING) {
                this->gsPtr->next_state();
                this->gsPtr->display();
            }

            QThread::sleep(1);
        }
        this->exec();
    }

private:
    void updateGameStatus(QString);

public slots:
    void textCommandExecuater(QString, QString);


};

#endif // STATE_WORKER_H
