#ifndef PLAYER_H
#define PLAYER_H
#include <QSound>



class Player : public QSound
{
    Q_OBJECT
private:
    QSound* backsound;
    QSound* sound1;
    QSound* sound2;
public:
    void play();
    void stop();
    ~Player();
    void setLoops(int l);
    void play1();
    void stop1();
    void play2();
    void stop2();
};

#endif // PLAYER_H
