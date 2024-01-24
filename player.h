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

#endif // PLAYER_H
