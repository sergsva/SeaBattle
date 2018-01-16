#include "smartplayer.h"

SmartPlayer::SmartPlayer()
{
flag = 1;
coordLastShooting.first = 0;
coordLastShooting.second = 0;
tempCoord.first = 0;
tempCoord.second = 0;
}

void SmartPlayer::Shooting()
{
    int antifor = 0;
    do
    {

    int route;

    if(antifor>30) flag = 2;
    int count = 0;
          switch (flag)
          {
           case 1:
               coordLastShooting.first = rand()%10;
               coordLastShooting.second = rand()%10;
               break;

           case 2:

              if(rand()%2)
              {
                   coordLastShooting.first = rand() % 10;
                   for(;count<10;count++)
                   {
                       if(fieldForNote->getValueFromField(qMakePair(coordLastShooting.first,count)) == "") break;
                   }
                   if(count!=10) coordLastShooting.second = count;
              }
              else
              {
                   coordLastShooting.second = rand() % 10;
                   for(;count<10;count++)
                   {
                       if(fieldForNote->getValueFromField(qMakePair(count,coordLastShooting.second)) == "") break;
                   }
                   if(count!=10) coordLastShooting.first = count;
              }
                          break;
          case 3:
coordLastShooting = qMakePair(tempCoord.first,tempCoord.second);
route = 1 + rand() % 4;
                                    switch (route)
                                              {
                                              case 1: if (coordLastShooting.first - 1 >= 0)
                                              {
                                                          coordLastShooting.first--;
                                              }
                                                      break;
                                              case 2: if (coordLastShooting.second + 1 < 10)
                                              {
                                                          coordLastShooting.second++;
                                              }
                                                      break;
                                              case 3: if (coordLastShooting.first + 1 < 10)
                                              {
                                                          coordLastShooting.first++;
                                              }
                                                      break;
                                              case 4: if (coordLastShooting.second - 1 >= 0)
                                              {
                                                          coordLastShooting.second--;
                                              }
                                                      break;
                                              }
                                    tempRoute = route;

              break;

                  case 4:
                                   switch (tempRoute)
                                          {
                                          case 1:
                                              if (coordLastShooting.first - 1 >= 0 && this->getValueFromFieldForNote(qMakePair(coordLastShooting.first - 1,coordLastShooting.second)) == "")
                                              {
                                                  coordLastShooting.first--;
                                              }
                                              else
                                              {
                                                  coordLastShooting.first++;
                                              }
                                              break;
                                          case 2: if (coordLastShooting.second + 1 < 10  && this->getValueFromFieldForNote(qMakePair(coordLastShooting.first,coordLastShooting.second + 1)) == "")
                                          {
                                                      coordLastShooting.second++;
                                          }
                                                  else
                                                  {
                                                      coordLastShooting.second--;
                                                  }
                                                  break;

                                          case 3: if (coordLastShooting.first + 1 < 10  && this->getValueFromFieldForNote(qMakePair(coordLastShooting.first + 1,coordLastShooting.second)) == "")
                                          {
                                                      coordLastShooting.first++;
                                          }
                                                  else
                                                  {
                                                      coordLastShooting.first--;
                                                  }
                                                  break;

                                          case 4: if (coordLastShooting.second - 1 >= 0 && this->getValueFromFieldForNote(qMakePair(coordLastShooting.first,coordLastShooting.second - 1)) == "")
                                          {
                                                      coordLastShooting.second--;
                                          }
                                                  else
                                                  {
                                                      coordLastShooting.second++;
                                                  }
                                                  break;
                                          }

                                          break;
antifor++;
}
    }while(this->getValueFromFieldForNote(qMakePair(coordLastShooting.first,coordLastShooting.second))!="");
          emit wasShoot();
}

void SmartPlayer::assessmentMyShotting(int value)
{
    if(value == 0)
    {
        fieldForNote->setValueInField("*",coordLastShooting);
        if(getCountShips()>4 && flag != 3 && flag != 4) this->flag = 1;
        if(getCountShips()<=4 && flag != 3 && flag != 4 ) this->flag = 2;
       if(flag == 4)  coordLastShooting = qMakePair(tempCoord.first,tempCoord.second);
        return;

    }
    if(value == 1)
    {
        fieldForNote->setValueInField("X",coordLastShooting);
        if(this->flag !=3 && this->flag !=4) {this->flag = 3; tempCoord = qMakePair(coordLastShooting.first,coordLastShooting.second); return;}
        if(this->flag ==3) {this->flag = 4;return;}

    }
    else
    {
    fieldForNote->setValueInField("X",coordLastShooting);
    if(getCountShips()>4) this->flag = 1;
    if(getCountShips()<=4) this->flag = 2;

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
