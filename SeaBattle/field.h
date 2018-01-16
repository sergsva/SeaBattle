#ifndef FIELD_H
#define FIELD_H
#include <QApplication>
#include<QVector>
#include<QString>

class Field
{

private:
QVector<QVector<QString> > field; //Поле в виде двумерного массива

public:
Field();
void setValueInField(QString value, QPair<int,int> coordinate);//Метод установки значения в поле по координате
QString getValueFromField(QPair<int, int> coordinate); //Метод получения значения из поля по координате
void clearField(); // Метод полного очищения поля
~Field();

};

#endif // FIELD_H
