#include "field.h"
#include<QException>

Field::Field()
{
field = { 10, QVector<QString>(10, "") };
}

void Field::setValueInField(QString value, QPair<int,int> coordinate)
    {

        if (coordinate.first >= 0 && coordinate.first < 10 && coordinate.second >= 0 && coordinate.second < 10)
        {
            this->field[coordinate.first][coordinate.second] = value;
        }
    }


QString Field::getValueFromField(QPair<int, int> coordinate)
    {
        return this->field[coordinate.first][coordinate.second];
    }

void Field::clearField()
    {
        this->field.clear();
        this->field = { 10, QVector<QString>(10, "") };
    }

Field::~Field()
    {
    this->field.clear();
    this->field.~QVector();
    }
