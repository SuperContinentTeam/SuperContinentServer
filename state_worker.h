#ifndef STATE_WORKER_H
#define STATE_WORKER_H

#include <QObject>
#include <QThread>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

#include "game_state.h"


class StateWorker : public QThread
{
    Q_OBJECT
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
    // 更新状态机的运行状态
    void updateGameStatus(const std::string &body);
    // 玩家动向（加入/离开）
    void playerAction(const QString &peer, const QJsonObject &body);
    // 聊天消息
    void chatMessage(const QString& peer, const QString& message);

public slots:
    void textCommandExecuater(QString, QString);

signals:
    void stateBoardcast(QString);
};

#endif // STATE_WORKER_H
