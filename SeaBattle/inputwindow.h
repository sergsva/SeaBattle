#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H
#include <QDialog>
#include"gamefield.h"
#include"field.h"
#include<QApplication>
#include<QVector>
#include<QString>

//Подключаем окно с ручным вводом
namespace Ui {
class DialogEditField;
}

class InputWindow: public QDialog
{
Q_OBJECT

public:
    explicit InputWindow(QWidget* parent = 0);
    GameField startGameField; // Поле для записи после заполнения
     void checkCountShips(); //Метод для отображения кол-ва кораблей в окне ручного ввода
    static QString convertValueIntToString(int& value); // Метод для перевода int в строку
    ~InputWindow();

private:
    Ui::DialogEditField * ui2; // Окно ввода
    QList<int> arrayLenthShips; // Список для хранения длин кораблей по количеству (1 палубные будут занесены, как 1 1 1 1)
    QList<int> arrayCountShips;// Список для хранения количества кораблей - для отображения на экране
    QPair<int, int> coordLastShip; // Координата последнего установленного корабля
    int lastDecker;//Хранит длину последнего корабля
    Route route; // Маршрут установки
    void paintToWindow(); // Вывод поля на экран программы


signals:
    void InputEnd(); //Сигнал - завершение ввода в окно, выход

public slots:
    void SlotManuallyInput(); // Слот ручной ввод, срабатывает на нажатие кнопки "Добавить"
    void SlotManuallyDelete();// Слот удаление, срабатывает на нажатие кнопки "Удалить"


};

#endif // INPUTWINDOW_H
