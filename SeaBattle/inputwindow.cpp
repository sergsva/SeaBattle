#include "inputwindow.h"
#include"ui_seabattle_input.h"
#include<QList>
#include"gamefield.h"


InputWindow::InputWindow(QWidget *parent): QDialog(parent), ui2(new Ui::DialogEditField)
{
ui2->setupUi(this);
coordLastShip.first = -1;
coordLastShip.second = -1;
arrayLenthShips<<4<<3<<3<<2<<2<<2<<1<<1<<1<<1;
checkCountShips();
QObject::connect(ui2->pushShip,SIGNAL(clicked()),this,SLOT(SlotManuallyInput()));
QObject::connect(ui2->popShip,SIGNAL(clicked()),this,SLOT(SlotManuallyDelete()));
QObject::connect(this,SIGNAL(InputEnd()),this,SLOT(close()));
}

void InputWindow::checkCountShips()
{
arrayCountShips.clear();
arrayCountShips<<0<<0<<0<<0;
qCount(arrayLenthShips.begin(),arrayLenthShips.end(),1,arrayCountShips[0]);
qCount(arrayLenthShips.begin(),arrayLenthShips.end(),2,arrayCountShips[1]);
qCount(arrayLenthShips.begin(),arrayLenthShips.end(),3,arrayCountShips[2]);
qCount(arrayLenthShips.begin(),arrayLenthShips.end(),4,arrayCountShips[3]);
ui2->countShip1->setText(InputWindow::convertValueIntToString(arrayCountShips[0]));
ui2->countShip2->setText(InputWindow::convertValueIntToString(arrayCountShips[1]));
ui2->countShip3->setText(InputWindow::convertValueIntToString(arrayCountShips[2]));
ui2->countShip4->setText(InputWindow::convertValueIntToString(arrayCountShips[3]));
}


QString InputWindow::convertValueIntToString(int & _value)
{
   QVariant temp;
   temp.setValue(_value);
   return temp.toString();
}


void InputWindow::SlotManuallyInput()
{
 int flag = 0;
 int firstLenth = arrayLenthShips.value(0);
 coordLastShip.second = ui2->horizontalSlider->value();
 coordLastShip.first= ui2->horizontalSlider_2->value();
if(ui2->radioButton_up->isChecked()==true) route = Up;
if(ui2->radioButton_right->isChecked()==true) route = Right;
if(ui2->radioButton_down->isChecked()==true) route = Down;
if(ui2->radioButton_left->isChecked()==true) route = Left;

if(firstLenth==1 && startGameField.isSetShipOnField(coordLastShip)==1)
{
    startGameField.setValueInField("O",coordLastShip);
    if(!arrayLenthShips.isEmpty())
    {

        ui2->text_info->append("Вы установили " + InputWindow::convertValueIntToString(firstLenth) + "-х палубный корабль!\n");
        arrayLenthShips.removeFirst();
    }
    flag++;
}
if(firstLenth!=1 && startGameField.drawShip(coordLastShip,route,firstLenth)==1)
{
     ui2->text_info->append("Вы установили " + InputWindow::convertValueIntToString(firstLenth) + "-х палубный корабль!\n");
       if(!arrayLenthShips.isEmpty()) arrayLenthShips.removeFirst();
       flag++;
}
if(flag==0)
{
    ui2->text_info->append("Сюда нельзя поставить " + InputWindow::convertValueIntToString(firstLenth) + "-х палубный корабль!\n");
}
paintToWindow();
checkCountShips();
if(arrayLenthShips.isEmpty())emit InputEnd();
}

void InputWindow::SlotManuallyDelete()
{
    int count = 0;
    int y = ui2->horizontalSlider->value();
    int x = ui2->horizontalSlider_2->value();
    if(startGameField.getValueFromField(qMakePair(x,y))!="O")
    {
         ui2->text_info->append("В этой ячейке нет корабля!\n");
        return;
    }
    else if(startGameField.isSetShipOnField(qMakePair(x,y))==1)
    {
        startGameField.setValueInField("",qMakePair(x,y));
         ui2->text_info->append("Вы удалили 1-х палубный корабль!\n");
        arrayLenthShips.push_back(1);
    }
    else
    {
startGameField.setValueInField("",qMakePair(x,y));
count++;
//Считаем кол-во палуб вверх по по полю
        for(;;)
         {
            if(x+1>9 || startGameField.getValueFromField(qMakePair(x + 1,y))=="") break;
            else
            {
                count++;
                startGameField.setValueInField("",qMakePair(++x,y));
            }
        }
        x = ui2->horizontalSlider_2->value();
//Считаем кол-во палуб вниз по полю
        for(;;)
     {
        if(x-1<0 || startGameField.getValueFromField(qMakePair(x - 1,y))=="") break;
        else
        {
            count++;
            startGameField.setValueInField("",qMakePair(--x,y));
        }
    }
x = ui2->horizontalSlider_2->value();
//Считаем кол-во палуб влево по полю
        for(;;)
    {
       if(y-1<0 || startGameField.getValueFromField(qMakePair(x,y - 1))=="") break;
        else
    {
        count++;
        startGameField.setValueInField("",qMakePair(x,--y));
    }
    }
y = ui2->horizontalSlider->value();
//Считаем кол-во палуб вправо по полю
       for(;;)
    {
    if(y+1>9 || startGameField.getValueFromField(qMakePair(x,y + 1))=="") break;
    else
    {
        count++;
        startGameField.setValueInField("",qMakePair(x,++y));
    }
    }
   ui2->text_info->append("Вы удалили " + InputWindow::convertValueIntToString(count) + "-х палубный корабль!\n");
   arrayLenthShips.push_back(count);
    }
   paintToWindow();
   checkCountShips();
}

void InputWindow::paintToWindow()
{

ui2->lineEdit_00->setText(startGameField.getValueFromField(qMakePair(0,0)));
if(ui2->lineEdit_00->text()=="O") ui2->lineEdit_00->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_00->setStyleSheet("background-color:White");
ui2->lineEdit_01->setText(startGameField.getValueFromField(qMakePair(0,1)));
if(ui2->lineEdit_01->text()=="O") ui2->lineEdit_01->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_01->setStyleSheet("background-color:White");
ui2->lineEdit_02->setText(startGameField.getValueFromField(qMakePair(0,2)));
if(ui2->lineEdit_02->text()=="O") ui2->lineEdit_02->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_02->setStyleSheet("background-color:White");
ui2->lineEdit_03->setText(startGameField.getValueFromField(qMakePair(0,3)));
if(ui2->lineEdit_03->text()=="O") ui2->lineEdit_03->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_03->setStyleSheet("background-color:White");
ui2->lineEdit_04->setText(startGameField.getValueFromField(qMakePair(0,4)));
if(ui2->lineEdit_04->text()=="O") ui2->lineEdit_04->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_04->setStyleSheet("background-color:White");
ui2->lineEdit_05->setText(startGameField.getValueFromField(qMakePair(0,5)));
if(ui2->lineEdit_05->text()=="O") ui2->lineEdit_05->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_05->setStyleSheet("background-color:White");
ui2->lineEdit_06->setText(startGameField.getValueFromField(qMakePair(0,6)));
if(ui2->lineEdit_06->text()=="O") ui2->lineEdit_06->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_07->setStyleSheet("background-color:White");
ui2->lineEdit_07->setText(startGameField.getValueFromField(qMakePair(0,7)));
if(ui2->lineEdit_07->text()=="O") ui2->lineEdit_07->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_07->setStyleSheet("background-color:White");
ui2->lineEdit_08->setText(startGameField.getValueFromField(qMakePair(0,8)));
if(ui2->lineEdit_08->text()=="O") ui2->lineEdit_08->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_08->setStyleSheet("background-color:White");
ui2->lineEdit_09->setText(startGameField.getValueFromField(qMakePair(0,9)));
if(ui2->lineEdit_09->text()=="O") ui2->lineEdit_09->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_09->setStyleSheet("background-color:White");
ui2->lineEdit_10->setText(startGameField.getValueFromField(qMakePair(1,0)));
if(ui2->lineEdit_10->text()=="O") ui2->lineEdit_10->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_10->setStyleSheet("background-color:White");
ui2->lineEdit_11->setText(startGameField.getValueFromField(qMakePair(1,1)));
if(ui2->lineEdit_11->text()=="O") ui2->lineEdit_11->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_11->setStyleSheet("background-color:White");
ui2->lineEdit_12->setText(startGameField.getValueFromField(qMakePair(1,2)));
if(ui2->lineEdit_12->text()=="O") ui2->lineEdit_12->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_12->setStyleSheet("background-color:White");
ui2->lineEdit_13->setText(startGameField.getValueFromField(qMakePair(1,3)));
if(ui2->lineEdit_13->text()=="O") ui2->lineEdit_13->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_13->setStyleSheet("background-color:White");
ui2->lineEdit_14->setText(startGameField.getValueFromField(qMakePair(1,4)));
if(ui2->lineEdit_14->text()=="O") ui2->lineEdit_14->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_14->setStyleSheet("background-color:White");
ui2->lineEdit_15->setText(startGameField.getValueFromField(qMakePair(1,5)));
if(ui2->lineEdit_15->text()=="O") ui2->lineEdit_15->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_15->setStyleSheet("background-color:White");
ui2->lineEdit_16->setText(startGameField.getValueFromField(qMakePair(1,6)));
if(ui2->lineEdit_16->text()=="O") ui2->lineEdit_16->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_16->setStyleSheet("background-color:White");
ui2->lineEdit_17->setText(startGameField.getValueFromField(qMakePair(1,7)));
if(ui2->lineEdit_17->text()=="O") ui2->lineEdit_17->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_17->setStyleSheet("background-color:White");
ui2->lineEdit_18->setText(startGameField.getValueFromField(qMakePair(1,8)));
if(ui2->lineEdit_18->text()=="O") ui2->lineEdit_18->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_18->setStyleSheet("background-color:White");
ui2->lineEdit_19->setText(startGameField.getValueFromField(qMakePair(1,9)));
if(ui2->lineEdit_19->text()=="O") ui2->lineEdit_19->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_19->setStyleSheet("background-color:White");
ui2->lineEdit_20->setText(startGameField.getValueFromField(qMakePair(2,0)));
if(ui2->lineEdit_20->text()=="O") ui2->lineEdit_20->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_20->setStyleSheet("background-color:White");
ui2->lineEdit_21->setText(startGameField.getValueFromField(qMakePair(2,1)));
if(ui2->lineEdit_21->text()=="O") ui2->lineEdit_21->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_21->setStyleSheet("background-color:White");
ui2->lineEdit_22->setText(startGameField.getValueFromField(qMakePair(2,2)));
if(ui2->lineEdit_22->text()=="O") ui2->lineEdit_22->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_22->setStyleSheet("background-color:White");
ui2->lineEdit_23->setText(startGameField.getValueFromField(qMakePair(2,3)));
if(ui2->lineEdit_23->text()=="O") ui2->lineEdit_23->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_23->setStyleSheet("background-color:White");
ui2->lineEdit_24->setText(startGameField.getValueFromField(qMakePair(2,4)));
if(ui2->lineEdit_24->text()=="O") ui2->lineEdit_24->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_24->setStyleSheet("background-color:White");
ui2->lineEdit_25->setText(startGameField.getValueFromField(qMakePair(2,5)));
if(ui2->lineEdit_25->text()=="O") ui2->lineEdit_25->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_25->setStyleSheet("background-color:White");
ui2->lineEdit_26->setText(startGameField.getValueFromField(qMakePair(2,6)));
if(ui2->lineEdit_26->text()=="O") ui2->lineEdit_26->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_26->setStyleSheet("background-color:White");
ui2->lineEdit_27->setText(startGameField.getValueFromField(qMakePair(2,7)));
if(ui2->lineEdit_27->text()=="O") ui2->lineEdit_27->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_27->setStyleSheet("background-color:White");
ui2->lineEdit_28->setText(startGameField.getValueFromField(qMakePair(2,8)));
if(ui2->lineEdit_28->text()=="O") ui2->lineEdit_28->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_28->setStyleSheet("background-color:White");
ui2->lineEdit_29->setText(startGameField.getValueFromField(qMakePair(2,9)));
if(ui2->lineEdit_29->text()=="O") ui2->lineEdit_29->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_29->setStyleSheet("background-color:White");
ui2->lineEdit_30->setText(startGameField.getValueFromField(qMakePair(3,0)));
if(ui2->lineEdit_30->text()=="O") ui2->lineEdit_30->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_30->setStyleSheet("background-color:White");
ui2->lineEdit_31->setText(startGameField.getValueFromField(qMakePair(3,1)));
if(ui2->lineEdit_31->text()=="O") ui2->lineEdit_31->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_31->setStyleSheet("background-color:White");
ui2->lineEdit_32->setText(startGameField.getValueFromField(qMakePair(3,2)));
if(ui2->lineEdit_32->text()=="O") ui2->lineEdit_32->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_32->setStyleSheet("background-color:White");
ui2->lineEdit_33->setText(startGameField.getValueFromField(qMakePair(3,3)));
if(ui2->lineEdit_33->text()=="O") ui2->lineEdit_33->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_33->setStyleSheet("background-color:White");
ui2->lineEdit_34->setText(startGameField.getValueFromField(qMakePair(3,4)));
if(ui2->lineEdit_34->text()=="O") ui2->lineEdit_34->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_34->setStyleSheet("background-color:White");
ui2->lineEdit_35->setText(startGameField.getValueFromField(qMakePair(3,5)));
if(ui2->lineEdit_35->text()=="O") ui2->lineEdit_35->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_35->setStyleSheet("background-color:White");
ui2->lineEdit_36->setText(startGameField.getValueFromField(qMakePair(3,6)));
if(ui2->lineEdit_36->text()=="O") ui2->lineEdit_36->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_36->setStyleSheet("background-color:White");
ui2->lineEdit_37->setText(startGameField.getValueFromField(qMakePair(3,7)));
if(ui2->lineEdit_37->text()=="O") ui2->lineEdit_37->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_37->setStyleSheet("background-color:White");
ui2->lineEdit_38->setText(startGameField.getValueFromField(qMakePair(3,8)));
if(ui2->lineEdit_38->text()=="O") ui2->lineEdit_38->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_38->setStyleSheet("background-color:White");
ui2->lineEdit_39->setText(startGameField.getValueFromField(qMakePair(3,9)));
if(ui2->lineEdit_39->text()=="O") ui2->lineEdit_39->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_39->setStyleSheet("background-color:White");
ui2->lineEdit_40->setText(startGameField.getValueFromField(qMakePair(4,0)));
if(ui2->lineEdit_40->text()=="O") ui2->lineEdit_40->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_40->setStyleSheet("background-color:White");
ui2->lineEdit_41->setText(startGameField.getValueFromField(qMakePair(4,1)));
if(ui2->lineEdit_41->text()=="O") ui2->lineEdit_41->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_41->setStyleSheet("background-color:White");
ui2->lineEdit_42->setText(startGameField.getValueFromField(qMakePair(4,2)));
if(ui2->lineEdit_42->text()=="O") ui2->lineEdit_42->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_42->setStyleSheet("background-color:White");
ui2->lineEdit_43->setText(startGameField.getValueFromField(qMakePair(4,3)));
if(ui2->lineEdit_43->text()=="O") ui2->lineEdit_43->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_43->setStyleSheet("background-color:White");
ui2->lineEdit_44->setText(startGameField.getValueFromField(qMakePair(4,4)));
if(ui2->lineEdit_44->text()=="O") ui2->lineEdit_44->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_44->setStyleSheet("background-color:White");
ui2->lineEdit_45->setText(startGameField.getValueFromField(qMakePair(4,5)));
if(ui2->lineEdit_45->text()=="O") ui2->lineEdit_45->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_45->setStyleSheet("background-color:White");
ui2->lineEdit_46->setText(startGameField.getValueFromField(qMakePair(4,6)));
if(ui2->lineEdit_46->text()=="O") ui2->lineEdit_46->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_46->setStyleSheet("background-color:White");
ui2->lineEdit_47->setText(startGameField.getValueFromField(qMakePair(4,7)));
if(ui2->lineEdit_47->text()=="O") ui2->lineEdit_47->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_47->setStyleSheet("background-color:White");
ui2->lineEdit_48->setText(startGameField.getValueFromField(qMakePair(4,8)));
if(ui2->lineEdit_48->text()=="O") ui2->lineEdit_48->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_48->setStyleSheet("background-color:White");
ui2->lineEdit_49->setText(startGameField.getValueFromField(qMakePair(4,9)));
if(ui2->lineEdit_49->text()=="O") ui2->lineEdit_49->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_49->setStyleSheet("background-color:White");
ui2->lineEdit_50->setText(startGameField.getValueFromField(qMakePair(5,0)));
if(ui2->lineEdit_50->text()=="O") ui2->lineEdit_50->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_50->setStyleSheet("background-color:White");
ui2->lineEdit_51->setText(startGameField.getValueFromField(qMakePair(5,1)));
if(ui2->lineEdit_51->text()=="O") ui2->lineEdit_51->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_51->setStyleSheet("background-color:White");
ui2->lineEdit_52->setText(startGameField.getValueFromField(qMakePair(5,2)));
if(ui2->lineEdit_52->text()=="O") ui2->lineEdit_52->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_52->setStyleSheet("background-color:White");
ui2->lineEdit_53->setText(startGameField.getValueFromField(qMakePair(5,3)));
if(ui2->lineEdit_53->text()=="O") ui2->lineEdit_53->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_53->setStyleSheet("background-color:White");
ui2->lineEdit_54->setText(startGameField.getValueFromField(qMakePair(5,4)));
if(ui2->lineEdit_54->text()=="O") ui2->lineEdit_54->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_54->setStyleSheet("background-color:White");
ui2->lineEdit_55->setText(startGameField.getValueFromField(qMakePair(5,5)));
if(ui2->lineEdit_55->text()=="O") ui2->lineEdit_55->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_55->setStyleSheet("background-color:White");
ui2->lineEdit_56->setText(startGameField.getValueFromField(qMakePair(5,6)));
if(ui2->lineEdit_56->text()=="O") ui2->lineEdit_56->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_56->setStyleSheet("background-color:White");
ui2->lineEdit_57->setText(startGameField.getValueFromField(qMakePair(5,7)));
if(ui2->lineEdit_57->text()=="O") ui2->lineEdit_57->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_57->setStyleSheet("background-color:White");
ui2->lineEdit_58->setText(startGameField.getValueFromField(qMakePair(5,8)));
if(ui2->lineEdit_58->text()=="O") ui2->lineEdit_58->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_58->setStyleSheet("background-color:White");
ui2->lineEdit_59->setText(startGameField.getValueFromField(qMakePair(5,9)));
if(ui2->lineEdit_59->text()=="O") ui2->lineEdit_59->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_59->setStyleSheet("background-color:White");
ui2->lineEdit_60->setText(startGameField.getValueFromField(qMakePair(6,0)));
if(ui2->lineEdit_60->text()=="O") ui2->lineEdit_60->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_60->setStyleSheet("background-color:White");
ui2->lineEdit_61->setText(startGameField.getValueFromField(qMakePair(6,1)));
if(ui2->lineEdit_61->text()=="O") ui2->lineEdit_61->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_61->setStyleSheet("background-color:White");
ui2->lineEdit_62->setText(startGameField.getValueFromField(qMakePair(6,2)));
if(ui2->lineEdit_62->text()=="O") ui2->lineEdit_62->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_62->setStyleSheet("background-color:White");
ui2->lineEdit_63->setText(startGameField.getValueFromField(qMakePair(6,3)));
if(ui2->lineEdit_63->text()=="O") ui2->lineEdit_63->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_63->setStyleSheet("background-color:White");
ui2->lineEdit_64->setText(startGameField.getValueFromField(qMakePair(6,4)));
if(ui2->lineEdit_64->text()=="O") ui2->lineEdit_64->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_64->setStyleSheet("background-color:White");
ui2->lineEdit_65->setText(startGameField.getValueFromField(qMakePair(6,5)));
if(ui2->lineEdit_65->text()=="O") ui2->lineEdit_65->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_65->setStyleSheet("background-color:White");
ui2->lineEdit_66->setText(startGameField.getValueFromField(qMakePair(6,6)));
if(ui2->lineEdit_66->text()=="O") ui2->lineEdit_66->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_66->setStyleSheet("background-color:White");
ui2->lineEdit_67->setText(startGameField.getValueFromField(qMakePair(6,7)));
if(ui2->lineEdit_67->text()=="O") ui2->lineEdit_67->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_67->setStyleSheet("background-color:White");
ui2->lineEdit_68->setText(startGameField.getValueFromField(qMakePair(6,8)));
if(ui2->lineEdit_68->text()=="O") ui2->lineEdit_68->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_68->setStyleSheet("background-color:White");
ui2->lineEdit_69->setText(startGameField.getValueFromField(qMakePair(6,9)));
if(ui2->lineEdit_69->text()=="O") ui2->lineEdit_69->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_69->setStyleSheet("background-color:White");
ui2->lineEdit_70->setText(startGameField.getValueFromField(qMakePair(7,0)));
if(ui2->lineEdit_70->text()=="O") ui2->lineEdit_70->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_70->setStyleSheet("background-color:White");
ui2->lineEdit_71->setText(startGameField.getValueFromField(qMakePair(7,1)));
if(ui2->lineEdit_71->text()=="O") ui2->lineEdit_71->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_71->setStyleSheet("background-color:White");
ui2->lineEdit_72->setText(startGameField.getValueFromField(qMakePair(7,2)));
if(ui2->lineEdit_72->text()=="O") ui2->lineEdit_72->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_72->setStyleSheet("background-color:White");
ui2->lineEdit_73->setText(startGameField.getValueFromField(qMakePair(7,3)));
if(ui2->lineEdit_73->text()=="O") ui2->lineEdit_73->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_73->setStyleSheet("background-color:White");
ui2->lineEdit_74->setText(startGameField.getValueFromField(qMakePair(7,4)));
if(ui2->lineEdit_74->text()=="O") ui2->lineEdit_74->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_74->setStyleSheet("background-color:White");
ui2->lineEdit_75->setText(startGameField.getValueFromField(qMakePair(7,5)));
if(ui2->lineEdit_75->text()=="O") ui2->lineEdit_75->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_75->setStyleSheet("background-color:White");
ui2->lineEdit_76->setText(startGameField.getValueFromField(qMakePair(7,6)));
if(ui2->lineEdit_76->text()=="O") ui2->lineEdit_76->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_76->setStyleSheet("background-color:White");
ui2->lineEdit_77->setText(startGameField.getValueFromField(qMakePair(7,7)));
if(ui2->lineEdit_77->text()=="O") ui2->lineEdit_77->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_77->setStyleSheet("background-color:White");
ui2->lineEdit_78->setText(startGameField.getValueFromField(qMakePair(7,8)));
if(ui2->lineEdit_78->text()=="O") ui2->lineEdit_78->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_78->setStyleSheet("background-color:White");
ui2->lineEdit_79->setText(startGameField.getValueFromField(qMakePair(7,9)));
if(ui2->lineEdit_79->text()=="O") ui2->lineEdit_79->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_79->setStyleSheet("background-color:White");
ui2->lineEdit_80->setText(startGameField.getValueFromField(qMakePair(8,0)));
if(ui2->lineEdit_80->text()=="O") ui2->lineEdit_80->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_80->setStyleSheet("background-color:White");
ui2->lineEdit_81->setText(startGameField.getValueFromField(qMakePair(8,1)));
if(ui2->lineEdit_81->text()=="O") ui2->lineEdit_81->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_81->setStyleSheet("background-color:White");
ui2->lineEdit_82->setText(startGameField.getValueFromField(qMakePair(8,2)));
if(ui2->lineEdit_82->text()=="O") ui2->lineEdit_82->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_82->setStyleSheet("background-color:White");
ui2->lineEdit_83->setText(startGameField.getValueFromField(qMakePair(8,3)));
if(ui2->lineEdit_83->text()=="O") ui2->lineEdit_83->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_83->setStyleSheet("background-color:White");
ui2->lineEdit_84->setText(startGameField.getValueFromField(qMakePair(8,4)));
if(ui2->lineEdit_84->text()=="O") ui2->lineEdit_84->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_84->setStyleSheet("background-color:White");
ui2->lineEdit_85->setText(startGameField.getValueFromField(qMakePair(8,5)));
if(ui2->lineEdit_85->text()=="O") ui2->lineEdit_85->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_85->setStyleSheet("background-color:White");
ui2->lineEdit_86->setText(startGameField.getValueFromField(qMakePair(8,6)));
if(ui2->lineEdit_86->text()=="O") ui2->lineEdit_86->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_86->setStyleSheet("background-color:White");
ui2->lineEdit_87->setText(startGameField.getValueFromField(qMakePair(8,7)));
if(ui2->lineEdit_87->text()=="O") ui2->lineEdit_87->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_87->setStyleSheet("background-color:White");
ui2->lineEdit_88->setText(startGameField.getValueFromField(qMakePair(8,8)));
if(ui2->lineEdit_88->text()=="O") ui2->lineEdit_88->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_88->setStyleSheet("background-color:White");
ui2->lineEdit_89->setText(startGameField.getValueFromField(qMakePair(8,9)));
if(ui2->lineEdit_89->text()=="O") ui2->lineEdit_89->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_89->setStyleSheet("background-color:White");
ui2->lineEdit_90->setText(startGameField.getValueFromField(qMakePair(9,0)));
if(ui2->lineEdit_90->text()=="O") ui2->lineEdit_90->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_90->setStyleSheet("background-color:White");
ui2->lineEdit_91->setText(startGameField.getValueFromField(qMakePair(9,1)));
if(ui2->lineEdit_91->text()=="O") ui2->lineEdit_91->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_91->setStyleSheet("background-color:White");
ui2->lineEdit_92->setText(startGameField.getValueFromField(qMakePair(9,2)));
if(ui2->lineEdit_92->text()=="O") ui2->lineEdit_92->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_92->setStyleSheet("background-color:White");
ui2->lineEdit_93->setText(startGameField.getValueFromField(qMakePair(9,3)));
if(ui2->lineEdit_93->text()=="O") ui2->lineEdit_93->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_93->setStyleSheet("background-color:White");
ui2->lineEdit_94->setText(startGameField.getValueFromField(qMakePair(9,4)));
if(ui2->lineEdit_94->text()=="O") ui2->lineEdit_94->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_94->setStyleSheet("background-color:White");
ui2->lineEdit_95->setText(startGameField.getValueFromField(qMakePair(9,5)));
if(ui2->lineEdit_95->text()=="O") ui2->lineEdit_95->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_95->setStyleSheet("background-color:White");
ui2->lineEdit_96->setText(startGameField.getValueFromField(qMakePair(9,6)));
if(ui2->lineEdit_96->text()=="O") ui2->lineEdit_96->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_96->setStyleSheet("background-color:White");
ui2->lineEdit_97->setText(startGameField.getValueFromField(qMakePair(9,7)));
if(ui2->lineEdit_97->text()=="O") ui2->lineEdit_97->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_97->setStyleSheet("background-color:White");
ui2->lineEdit_98->setText(startGameField.getValueFromField(qMakePair(9,8)));
if(ui2->lineEdit_98->text()=="O") ui2->lineEdit_98->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_98->setStyleSheet("background-color:White");
ui2->lineEdit_99->setText(startGameField.getValueFromField(qMakePair(9,9)));
if(ui2->lineEdit_99->text()=="O") ui2->lineEdit_99->setStyleSheet("background-color:SkyBlue");
else ui2->lineEdit_99->setStyleSheet("background-color:White");

}


InputWindow::~InputWindow()
{
delete ui2;
}
