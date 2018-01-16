#include "gamefield.h"

bool GameField::drawShip(QPair<int, int> coordinate, int rand_number_route, int lenth_ships)
      {
          switch (rand_number_route)
          {
          case Up:
              if (coordinate.first - lenth_ships + 1 < 0) return 0; // проверяем границы
              for (int i = 0; i < lenth_ships; i++) // проходим все цепочку по месту возможной установки и проверяем, что можем поставить каждую часть
              {
                  if (!this->isSetShipOnField(qMakePair(coordinate.first - i, coordinate.second))) return 0;
              }
              for (int i = 0; i < lenth_ships; i++)// устанавливаем корабль на игровое поле
              {
                  this->setValueInField("O", qMakePair(coordinate.first - i, coordinate.second));

              }
              break;

          case Right:
              if ((coordinate.second + lenth_ships - 1) > 10) return 0;
              for (int i = 0; i < lenth_ships; i++)
              {
                  if (!this->isSetShipOnField(qMakePair(coordinate.first, coordinate.second + i))) return 0;
              }

              for (int i = 0; i < lenth_ships; i++)
              {
                  this->setValueInField("O", qMakePair(coordinate.first, coordinate.second + i));
              }
              break;

          case Down:
              if ((coordinate.first + lenth_ships - 1) > 10) return 0;
              for (int i = 0; i < lenth_ships; i++)
              {
                  if (!this->isSetShipOnField(qMakePair(coordinate.first + i, coordinate.second))) return 0;
              }
              for (int i = 0; i < lenth_ships; i++)
              {
                  this->setValueInField("O", qMakePair(coordinate.first + i, coordinate.second));
              }
              break;

          case Left:
              if ((coordinate.second - lenth_ships + 1) < 0) return 0;
              for (int i = 0; i < lenth_ships; i++)
              {
                  if (!this->isSetShipOnField(qMakePair(coordinate.first, coordinate.second - i))) return 0;
              }

              for (int i = 0; i < lenth_ships; i++)
              {
                  this->setValueInField("O", qMakePair(coordinate.first, coordinate.second - i));
              }
              break;
          }
          return 1;
      }


bool GameField::isSetShipOnField(QPair<int, int> coordinate)
            {
//Проверяем саму ячейку и обходим ее по кругу
                if ((coordinate.first >= 0 && coordinate.first<10) && (coordinate.second >= 0 && coordinate.second<10))
                {

                  if (this->getValueFromField(coordinate) == "O") return 0;
                }
                else return 0;

                for (size_t i = 1; i < 9; i++)
                {                   
                    if(i==1)
                    {
                        coordinate.first--;
                        coordinate.second--;
                    }
                    else if (i>1 && i <= 3) coordinate.second++;
                    else if (i>3 && i<=5) coordinate.first++;
                    else if (i>5 && i<8) coordinate.second--;
                    else coordinate.first--;

                    if ((coordinate.first >= 0 && coordinate.first<10) && (coordinate.second >= 0 && coordinate.second<10))
                    {

                      if (this->getValueFromField(coordinate) == "O") return 0;
                    }
                }

                return 1;
            }

