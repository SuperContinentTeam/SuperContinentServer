#ifndef PLAYER_H
#define PLAYER_H
#include<QObject>
class Player
{
public:
    Player(QString, QString);

    QString name;
    QString peer;
};

typedef std::shared_ptr<Player> PlayerPtr;

#endif // PLAYER_H
