#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <QObject>
#include <QDebug>
#include <QThread>

#include "player.h"

class GameState: public QObject
{
    Q_OBJECT

    QMap<QString, PlayerPtr> playerMap;

public:
    quint32 tick = 0;       // 时间刻
    quint8 worldSize = 0;   // 世界尺寸

    GameState(quint8);
    ~GameState();

    enum Status {
        INIT=0,    // 初始
        RUNING=1,  // 运行
        PAUSE=2,   // 暂停
        END=3      // 中止
    };
    Status status = Status::INIT;

    void next_state();
    void display();

    void playerJoin(QString peer, PlayerPtr player);
    void playerLeave(QString peer);
};

typedef std::shared_ptr<GameState> GameStatePtr;

#endif // GAME_STATE_H
