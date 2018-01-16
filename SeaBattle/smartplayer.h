#ifndef SMARTPLAYER_H
#define SMARTPLAYER_H
#include"player.h"
#include<algorithm>
class SmartPlayer : public QObject, public Player
{
Q_OBJECT
private:
QPair<int,int> tempCoord;
int tempRoute;
    int flag;
public:
    SmartPlayer();
    void assessmentMyShotting(int value); //Метод, который обрабатывает результат стрельбы, т.е. после стрельбы мы передаем
    //координату выстрела, и от соперника полуем значение попал, ранил, ублил
void Shooting(); //Стрельба ПК с логикой
void toNull()
{
    tempCoord.first = 0;
    tempCoord.second = 0;
    flag = 1;
}

signals:
void wasShoot();//Сигнал - выстрел сделан - обработать его
};

#endif // SMARTPLAYER_H
