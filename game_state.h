#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <QObject>
#include <QDebug>
#include <QThread>

class GameState: public QObject
{
    Q_OBJECT

public:
    quint32 tick = 0;       // 时间刻
    quint8 worldSize = 0;   // 世界尺寸
    GameState(quint8);
    ~GameState();

    bool isPause = true;    // 暂停状态
    bool isEnd = false;     // 结束状态

    void next_state();
    void show_current_status();

public slots:
    void run();
};

typedef std::shared_ptr<GameState> GameStatePtr;

#endif // GAME_STATE_H
