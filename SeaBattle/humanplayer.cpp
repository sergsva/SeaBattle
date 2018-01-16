#include "humanplayer.h"
#include"inputwindow.h"



void HumanPlayer::assessmentMyShotting(int value)
{
    if(value == 0)
    {
      this->setValueInFieldForNote("*",coordLastShooting); return;
    }
     this->setValueInFieldForNote("X",coordLastShooting);

    if(value == 2)
    {
        //Вокруг убитого корабля рисуем точки в поле для заметок
       int count = 0;
        while (coordLastShooting.first + count < 10 && fieldForNote->getValueFromField(qMakePair(coordLastShooting.first + count, coordLastShooting.second)) == "X")
        {
            markDeathShip(qMakePair(coordLastShooting.first + count, coordLastShooting.second));
            count++;
        }
        count = 0;
        while (coordLastShooting.first - count >=0 && fieldForNote->getValueFromField(qMakePair(coordLastShooting.first - count, coordLastShooting.second)) == "X" )
        {
           markDeathShip(qMakePair(coordLastShooting.first - count, coordLastShooting.second));
            count++;
        }
        count = 0;
        while (coordLastShooting.second + count < 10 && fieldForNote->getValueFromField(qMakePair(coordLastShooting.first, coordLastShooting.second + count)) == "X")
    {
           markDeathShip(qMakePair(coordLastShooting.first, coordLastShooting.second + count));
            count++;
        }
        count = 0;
        while (coordLastShooting.second - count >=0 && fieldForNote->getValueFromField(qMakePair(coordLastShooting.first, coordLastShooting.second - count)) == "X")
        {
              markDeathShip(qMakePair(coordLastShooting.first, coordLastShooting.second - count));
            count++;
        }

    }


}
