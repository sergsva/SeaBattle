#include "player.h"

Player::Player()
{
             countShips = 10;
            this->fieldForGame = new GameField();
            this->fieldForNote = new Field();
            this->lastFieldForGame = new GameField();
}

int Player::getCountShips()
    {
        return countShips;
    }

void Player::destroyedShip()
    {
        countShips--;
    }

void Player::replaceFields(GameField newFieldfieldForGame)
{
    for(int i =0;i<10;i++)
    {
        for(int j =0;j<10;j++)
        {
    fieldForGame->setValueInField(newFieldfieldForGame.getValueFromField(qMakePair(i,j)),qMakePair(i,j));
        }
    }
fieldForNote->clearField();
}

void Player::recSituationOnFields()
{
    for(int i =0;i<10;i++)
    {
        for(int j =0;j<10;j++)
        {
    lastFieldForGame->setValueInField(fieldForGame->getValueFromField(qMakePair(i,j)),qMakePair(i,j));
        }
    }
     fieldForNote->clearField();
}

void Player::replaceFieldsOnLastFields()
{
    for(int i =0;i<10;i++)
    {
        for(int j =0;j<10;j++)
        {
fieldForGame->setValueInField(lastFieldForGame->getValueFromField(qMakePair(i,j)),qMakePair(i,j));
        }
    }
    fieldForNote->clearField();
}

QPair<int,int> Player::getCoordLastShooting()
{
    return coordLastShooting;
}

void Player::setCoordLastShooting(QPair<int,int> shoot)//установить координату последнего хода
{
    coordLastShooting.first = shoot.first;
    coordLastShooting.second = shoot.second;
}

int Player::assessmentShottingOpponent(QPair<int, int> coordinate)
{

    if(this->getValueFromFieldForGame(coordinate) !="O")
    {
        this->setValueInFieldForGame("*",coordinate);
        return 0;
    }

   else
    {
        this->setValueInFieldForGame("X",coordinate);
        if(isDestroedShip(coordinate) == 0)
        {
           return 1;
        }
        else
        {
           this->destroyedShip(); return 2;
        }

    }
}


void Player::markDeathShip(QPair<int, int> coordinate)
{
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
            if (fieldForNote->getValueFromField(coordinate) == "") fieldForNote->setValueInField("*", coordinate);
        }
    }
}

bool Player::isDestroedShip(QPair<int, int> coordinate)
{
    int count = 0, flag = 0;
    while (coordinate.first + count < 10 && fieldForGame->getValueFromField(qMakePair(coordinate.first + count, coordinate.second)) != "" && fieldForGame->getValueFromField(qMakePair(coordinate.first + count, coordinate.second)) != "*")
    {
        if (fieldForGame->getValueFromField(qMakePair(coordinate.first + count, coordinate.second)) == "O")
        {
            flag++;
        }
        count++;
    }
    count = 0;
    while (coordinate.first - count >=0 && fieldForGame->getValueFromField(qMakePair(coordinate.first - count, coordinate.second)) != "" && fieldForGame->getValueFromField(qMakePair(coordinate.first - count, coordinate.second)) != "*")
    {
        if (fieldForGame->getValueFromField(qMakePair(coordinate.first - count, coordinate.second)) == "O")
        {
            flag++;
        }
        count++;
    }
    count = 0;
    while (coordinate.second + count < 10 && fieldForGame->getValueFromField(qMakePair(coordinate.first, coordinate.second + count)) != "" && fieldForGame->getValueFromField(qMakePair(coordinate.first, coordinate.second + count)) != "*")
{
        if (fieldForGame->getValueFromField(qMakePair(coordinate.first, coordinate.second + count)) == "O")
        {
            flag++;
        }
        count++;
    }
    count = 0;
    while (coordinate.second - count >=0 && fieldForGame->getValueFromField(qMakePair(coordinate.first, coordinate.second - count)) != "" && fieldForGame->getValueFromField(qMakePair(coordinate.first, coordinate.second - count)) != "*")
    {
        if (fieldForGame->getValueFromField(qMakePair(coordinate.first, coordinate.second - count)) == "O")
        {
            flag++;
        }
        count++;
    }

    if (flag)
    {
        return 0;
    }
    return 1;
}

void Player::setValueInFieldForGame(QString value, QPair<int,int> coordinate)
{
    this->fieldForGame->setValueInField(value,coordinate);
}

QString Player::getValueFromFieldForGame(QPair<int, int> coordinate)
{
    return this->fieldForGame->getValueFromField(coordinate);
}

void Player::setValueInFieldForNote(QString value, QPair<int,int> coordinate)
{
    this->fieldForNote->setValueInField(value,coordinate);
}

QString Player::getValueFromFieldForNote(QPair<int, int> coordinate)
{
     return this->fieldForNote->getValueFromField(coordinate);
}

void Player::clearFields()
{
    this->fieldForGame->clearField();
  this-> fieldForNote->clearField();
   this->countShips=10;
}

void Player::SlotAutoFiilGameField()
    {
        int count = 1, lenth_ships = 4;
        while (lenth_ships)
        {
            int count_ships = count;
            while (count_ships)
            {
                int rand_i = rand() % 10;
                int rand_j = rand() % 10;
                int route = rand() % 4 + 1;
                if (fieldForGame->drawShip(qMakePair(rand_i, rand_j), route, lenth_ships))
                {
                    count_ships--;
                }
            }
            count++;
            lenth_ships--;
        }

    }

Player::~Player()
{
    delete fieldForGame;
    delete fieldForNote;
    delete lastFieldForGame;

}
