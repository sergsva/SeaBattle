#ifndef PLAYER_H
#define PLAYER_H
#include"gamefield.h"


class Player
{

public:
Player();
~Player();
int getCountShips(); // Возрващает текущее кол-во кораблей у игрока
void destroyedShip(); // Снижает счетчик кораблей у игрока на 1
void markDeathShip(QPair<int, int> coordinate);//Функция, которая после уничтожения корабля рисует точки вокруг него на поле заметок игрока
bool isDestroedShip(QPair<int, int> coordinate);//Тест на сбитие корабля после попадания
void clearFields();// Очистить все имещиеся поля у игрока
QString getValueFromFieldForGame(QPair<int, int> coordinate); // Получить значение из игрового поля по координате
QString getValueFromFieldForNote(QPair<int, int> coordinate); // Получить значение из поля для заметок по координате
void setValueInFieldForGame(QString value, QPair<int,int> coordinate);// Установить значение в игровое поле по координате
void setValueInFieldForNote(QString value, QPair<int,int> coordinate);// Установить значение в поле для заметок по координате
void replaceFields(GameField newFieldFieldForGame);//Заменить игровое поле игрока на другое
void recSituationOnFields(); //Сохранить начальную конфигурацию игрового поля
void replaceFieldsOnLastFields();// В случае начала текущей игры заново, установить игровые поля в начальный вид
QPair<int,int> getCoordLastShooting();//Получить координату последнего хода
void setCoordLastShooting(QPair<int,int> shoot);//Установить координату последнего хода
int assessmentShottingOpponent(QPair<int, int> coordinate);//Метод который проверяет куда попал соперник и возвращает тип попадания 0 - мимо, 1 - ранил, 2 - убил
virtual void assessmentMyShotting(int flag) = 0;// Метод, который обрабатывает после стрельбы результаты полученные от соперника


public slots:
void SlotAutoFiilGameField(); // Слот автоматическое заполнение поля

protected:
int countShips; //Количество кораблей игрока
QPair<int,int> coordLastShooting; //Последний ход
GameField* lastFieldForGame;//Копия игрового поля в начале игры, для функции "Начать игру заново"
GameField *fieldForGame; // Игровое поле
Field *fieldForNote; // Поле для заметок

};

#endif // PLAYER_H
