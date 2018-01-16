#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include"player.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer(){}
    void assessmentMyShotting(int value);//Метод, который обрабатывает результат стрельбы, т.е. после стрельбы мы передаем
    //координату выстрела, и от соперника полуем значение попал, ранил, убил
};

#endif // HUMANPLAYER_H
