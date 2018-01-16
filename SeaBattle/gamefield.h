#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include"field.h"
#include<QPair>

enum Route { Up = 1, Right, Down, Left }; // Для упрощения движения по полю, указывает направление

class GameField : public Field
{

public:
 GameField(){}
bool drawShip(QPair<int, int> coordinate, int rand_number_route, int lenth_ships); // Метод, который рисует корабль на игровом поле,
//т.е. устанавливает знаяение в поле, принимает (координату начала корабля, направление и длину),
//возвращает 1 - установлено, или 0 - неудачно

bool isSetShipOnField(QPair<int, int> Coordinate);//Метод проверяет, можно ли установить в эту ячейку часть корабля
};

#endif // GAMEFIELD_H
