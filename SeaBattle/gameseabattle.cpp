#include "gameseabattle.h"
#include"ui_gameseabattle.h"
#include <QThread>

GameSeaBattle::GameSeaBattle(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
ui->setupUi(this);
inputWnd = new InputWindow(this);
human = new HumanPlayer();
pc = new SmartPlayer();
SlotHideInterface();
ui->action_player->setChecked(true);
ui->action_pc->setChecked(false);
ui->action_auto->setChecked(true);
ui->action_mun->setChecked(false);
gameStart = 0;
connect(ui->action_Newgame,SIGNAL(triggered()), this, SLOT(SlotClickNewGame()));
connect(ui->action_newbattle,SIGNAL(triggered()), this, SLOT(SlotClickNewBattle()));
connect(ui->action_mun,SIGNAL(triggered()),this, SLOT(SlotSetManFillField()));
connect(ui->action_auto,SIGNAL(triggered()),this, SLOT(SlotSetAutoFillField()));
connect(ui->action_player,SIGNAL(triggered()),this, SLOT(SlotSetFirstStepPlayer()));
connect(ui->action_pc,SIGNAL(triggered()),this, SLOT(SlotSetFirstStepPC()));
connect(inputWnd, SIGNAL(InputEnd()),this, SLOT(SlotRecFromFormToPlayer()));
connect(inputWnd, SIGNAL(InputEnd()),SIGNAL(SignalViewPlayerField()));
connect(this,SIGNAL(SignalViewPlayerField()),this,SLOT(SlotPaintToMainWindow()));
connect(this,SIGNAL(SignalViewPlayerField()),this,SLOT(SlotPaintToNoteWindow()));
connect(pc, SIGNAL(wasShoot()),this,SLOT(SlotAfterShoot()));
connect(ui->pushButton_Fire,SIGNAL(clicked()),this,SLOT(SlotAfterShoot()));
}


void GameSeaBattle::SlotHideInterface()
{
    ui->pushButton_Fire->hide();
    ui->label_text->hide();
    ui->textEdit->hide();
    ui->horizontalSlider_X->hide();
    ui->labeld_A->hide();
    ui->labeld_B->hide();
    ui->labeld_C->hide();
    ui->labeld_D->hide();
    ui->labeld_E->hide();
    ui->labeld_F->hide();
    ui->labeld_G->hide();
    ui->labeld_H->hide();
    ui->labeld_I->hide();
    ui->labeld_K->hide();
    ui->horizontalSlider_Y->hide();
    ui->labeld_1->hide();
    ui->labeld_2->hide();
    ui->labeld_3->hide();
    ui->labeld_4->hide();
    ui->labeld_5->hide();
    ui->labeld_6->hide();
    ui->labeld_7->hide();
    ui->labeld_8->hide();
    ui->labeld_9->hide();
    ui->labeld_10->hide();

}

void GameSeaBattle::SlotClickNewGame()
{
    ui->textEdit->clear();
    setInfoToLabelText("Вы начали новую игру!");
    human->clearFields();
    emit SignalViewPlayerField();
    pc->clearFields();
    pc->toNull();
   if(this->gameStart == 0)
        {
         ui->pushButton_Fire->setHidden(false);
         ui->label_text->setHidden(false);
         ui->textEdit->setHidden(false);
         ui->horizontalSlider_X->setHidden(false);
         ui->labeld_A->setHidden(false);
         ui->labeld_B->setHidden(false);
         ui->labeld_C->setHidden(false);
         ui->labeld_D->setHidden(false);
         ui->labeld_E->setHidden(false);
         ui->labeld_F->setHidden(false);
         ui->labeld_G->setHidden(false);
         ui->labeld_H->setHidden(false);
         ui->labeld_I->setHidden(false);
         ui->labeld_K->setHidden(false);
         ui->horizontalSlider_Y->setHidden(false);
         ui->labeld_1->setHidden(false);
         ui->labeld_2->setHidden(false);
         ui->labeld_3->setHidden(false);
         ui->labeld_4->setHidden(false);
         ui->labeld_5->setHidden(false);
         ui->labeld_6->setHidden(false);
         ui->labeld_7->setHidden(false);
         ui->labeld_8->setHidden(false);
         ui->labeld_9->setHidden(false);
         ui->labeld_10->setHidden(false);
         ui->img1->setHidden(true);
          ui->img2->setHidden(true);
           ui->img3->setHidden(true);
    }

       if(ui->action_mun->isChecked()==true) {inputWnd->show();}
        else
        {
           human->SlotAutoFiilGameField();
           setInfoToLabelText("Ваши корабли были размещены автоматически!");
           emit SignalViewPlayerField();
        }
        pc->SlotAutoFiilGameField();

        gameStart = true;
        human->recSituationOnFields();
        pc->recSituationOnFields();

if (ui->action_player->isChecked()==true)
{
   setInfoToLabelText("Ваш ход!");
 queueShooting = 0;
}
    else
{
 queueShooting = 1;
    pc->Shooting();

}

 }

void GameSeaBattle::SlotClickNewBattle()
{
    if(this->gameStart == 1)
    {

      setInfoToLabelText("Вы начали последний бой заново!");
      human->replaceFieldsOnLastFields();
      pc->replaceFieldsOnLastFields();
emit SignalViewPlayerField();
      if (ui->action_player->isChecked()==true)
      {
            setInfoToLabelText("Ваш ход!");
     queueShooting = 0;
      }
          else
      {
           setInfoToLabelText("Ход соперника!");
           queueShooting = 1;
          pc->Shooting();

      }
    }



}

void GameSeaBattle::SlotAfterShoot() //обработка сигнала после стрельбы
    {
   int result;
  if( queueShooting == -1)return;
if( queueShooting == 0)
{
    if( human->getValueFromFieldForNote(qMakePair(ui->horizontalSlider_Y->value(),ui->horizontalSlider_X->value()))!="") {setInfoToLabelText("Вы не можете сюда стрелять!");return;}
    human->setCoordLastShooting(qMakePair(ui->horizontalSlider_Y->value(), ui->horizontalSlider_X->value()));
   result = pc->assessmentShottingOpponent(qMakePair(ui->horizontalSlider_Y->value(), ui->horizontalSlider_X->value()));
   human->assessmentMyShotting(result);
   emit SignalViewPlayerField();
   if(pc->getCountShips()==0){ setInfoToLabelText("Игра окончена! Вы победили!"); queueShooting = -1; return;}
  if(result == 0){ setInfoToLabelText("Вы промазали!");queueShooting = 1; pc->Shooting();return;}
   if(result == 1){setInfoToLabelText("Ранили, стреляйте повторно!");}
   else { setInfoToLabelText("Убили корабль соперника, стреляйте повторно!");}
}
else
{
setInfoToLabelText("Компьютер стреляет!");
result=human->assessmentShottingOpponent(pc->getCoordLastShooting());
pc->assessmentMyShotting(result);
emit SignalViewPlayerField();
if(human->getCountShips()==0) {setInfoToLabelText("Игра окончена! Компьютер победил!"); queueShooting = -1; return;}
if(result == 0)
{
setInfoToLabelText("Компьютер промазал!\n\nВаш ход!");
     queueShooting = 0; return;
}
if(result == 1)
{
setInfoToLabelText("Компьютер попал и стреляет повторно!");
emit SignalViewPlayerField();
    pc->Shooting();
}
else
{
setInfoToLabelText("Компьютер потопил ваш корабль и стреляет повторно!");
    pc->Shooting();
}

}
 }



void GameSeaBattle::setInfoToLabelText(const QString &str)
{
    ui->textEdit->append(str + "\n");
}

void GameSeaBattle::SlotSetFirstStepPlayer()
{
    if(ui->action_player->isChecked()==true) ui->action_pc->setChecked(false);
    else ui->action_pc->setChecked(true);
}

void GameSeaBattle::SlotSetFirstStepPC()
{
     if(ui->action_pc->isChecked()==true) ui->action_player->setChecked(false);
     else ui->action_player->setChecked(true);
}

void GameSeaBattle::SlotSetAutoFillField()
{
    if(ui->action_auto->isChecked()==true) ui->action_mun->setChecked(false);
    else ui->action_mun->setChecked(true);
}

void GameSeaBattle::SlotSetManFillField()
{
    if(ui->action_mun->isChecked()==true) ui->action_auto->setChecked(false);
   else ui->action_auto->setChecked(true);
}


void GameSeaBattle::SlotRecFromFormToPlayer()
{
    human->replaceFields(inputWnd->startGameField);
    setInfoToLabelText("Вы разместили свои корабли вручную!");
}

void GameSeaBattle::SlotPaintToMainWindow()
{

ui->GF_00->setText(human->getValueFromFieldForGame(qMakePair(0,0)));
if(ui->GF_00->text()=="O") ui->GF_00->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_00->text()=="X")ui->GF_00->setStyleSheet("background-color:Grey");
else ui->GF_00->setStyleSheet("background-color:White");

ui->GF_01->setText(human->getValueFromFieldForGame(qMakePair(0,1)));
if(ui->GF_01->text()=="O") ui->GF_01->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_01->text()=="X")ui->GF_01->setStyleSheet("background-color:Grey");
else ui->GF_01->setStyleSheet("background-color:White");

ui->GF_02->setText(human->getValueFromFieldForGame(qMakePair(0,2)));
if(ui->GF_02->text()=="O") ui->GF_02->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_02->text()=="X")ui->GF_02->setStyleSheet("background-color:Grey");
else ui->GF_02->setStyleSheet("background-color:White");

ui->GF_03->setText(human->getValueFromFieldForGame(qMakePair(0,3)));
if(ui->GF_03->text()=="O") ui->GF_03->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_03->text()=="X")ui->GF_03->setStyleSheet("background-color:Grey");
else ui->GF_03->setStyleSheet("background-color:White");

ui->GF_04->setText(human->getValueFromFieldForGame(qMakePair(0,4)));
if(ui->GF_04->text()=="O") ui->GF_04->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_04->text()=="X")ui->GF_04->setStyleSheet("background-color:Grey");
else ui->GF_04->setStyleSheet("background-color:White");

ui->GF_05->setText(human->getValueFromFieldForGame(qMakePair(0,5)));
if(ui->GF_05->text()=="O") ui->GF_05->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_05->text()=="X")ui->GF_05->setStyleSheet("background-color:Grey");
else ui->GF_05->setStyleSheet("background-color:White");

ui->GF_06->setText(human->getValueFromFieldForGame(qMakePair(0,6)));
if(ui->GF_06->text()=="O") ui->GF_06->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_06->text()=="X")ui->GF_06->setStyleSheet("background-color:Grey");
else ui->GF_06->setStyleSheet("background-color:White");

ui->GF_07->setText(human->getValueFromFieldForGame(qMakePair(0,7)));
if(ui->GF_07->text()=="O") ui->GF_07->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_07->text()=="X")ui->GF_07->setStyleSheet("background-color:Grey");
else ui->GF_07->setStyleSheet("background-color:White");

ui->GF_08->setText(human->getValueFromFieldForGame(qMakePair(0,8)));
if(ui->GF_08->text()=="O") ui->GF_08->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_08->text()=="X")ui->GF_08->setStyleSheet("background-color:Grey");
else ui->GF_08->setStyleSheet("background-color:White");

ui->GF_09->setText(human->getValueFromFieldForGame(qMakePair(0,9)));
if(ui->GF_09->text()=="O") ui->GF_09->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_09->text()=="X")ui->GF_09->setStyleSheet("background-color:Grey");
else ui->GF_09->setStyleSheet("background-color:White");

ui->GF_10->setText(human->getValueFromFieldForGame(qMakePair(1,0)));
if(ui->GF_10->text()=="O") ui->GF_10->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_10->text()=="X")ui->GF_10->setStyleSheet("background-color:Grey");
else ui->GF_10->setStyleSheet("background-color:White");

ui->GF_11->setText(human->getValueFromFieldForGame(qMakePair(1,1)));
if(ui->GF_11->text()=="O") ui->GF_11->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_11->text()=="X")ui->GF_11->setStyleSheet("background-color:Grey");
else ui->GF_11->setStyleSheet("background-color:White");

ui->GF_12->setText(human->getValueFromFieldForGame(qMakePair(1,2)));
if(ui->GF_12->text()=="O") ui->GF_12->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_12->text()=="X")ui->GF_12->setStyleSheet("background-color:Grey");
else ui->GF_12->setStyleSheet("background-color:White");

ui->GF_13->setText(human->getValueFromFieldForGame(qMakePair(1,3)));
if(ui->GF_13->text()=="O") ui->GF_13->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_13->text()=="X")ui->GF_13->setStyleSheet("background-color:Grey");
else ui->GF_13->setStyleSheet("background-color:White");

ui->GF_14->setText(human->getValueFromFieldForGame(qMakePair(1,4)));
if(ui->GF_14->text()=="O") ui->GF_14->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_14->text()=="X")ui->GF_14->setStyleSheet("background-color:Grey");
else ui->GF_14->setStyleSheet("background-color:White");

ui->GF_15->setText(human->getValueFromFieldForGame(qMakePair(1,5)));
if(ui->GF_15->text()=="O") ui->GF_15->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_15->text()=="X")ui->GF_15->setStyleSheet("background-color:Grey");
else ui->GF_15->setStyleSheet("background-color:White");

ui->GF_16->setText(human->getValueFromFieldForGame(qMakePair(1,6)));
if(ui->GF_16->text()=="O") ui->GF_16->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_16->text()=="X")ui->GF_16->setStyleSheet("background-color:Grey");
else ui->GF_16->setStyleSheet("background-color:White");

ui->GF_17->setText(human->getValueFromFieldForGame(qMakePair(1,7)));
if(ui->GF_17->text()=="O") ui->GF_17->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_17->text()=="X")ui->GF_17->setStyleSheet("background-color:Grey");
else ui->GF_17->setStyleSheet("background-color:White");

ui->GF_18->setText(human->getValueFromFieldForGame(qMakePair(1,8)));
if(ui->GF_18->text()=="O") ui->GF_18->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_18->text()=="X")ui->GF_18->setStyleSheet("background-color:Grey");
else ui->GF_18->setStyleSheet("background-color:White");

ui->GF_19->setText(human->getValueFromFieldForGame(qMakePair(1,9)));
if(ui->GF_19->text()=="O") ui->GF_19->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_19->text()=="X")ui->GF_19->setStyleSheet("background-color:Grey");
else ui->GF_19->setStyleSheet("background-color:White");

ui->GF_20->setText(human->getValueFromFieldForGame(qMakePair(2,0)));
if(ui->GF_20->text()=="O") ui->GF_20->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_20->text()=="X")ui->GF_20->setStyleSheet("background-color:Grey");
else ui->GF_20->setStyleSheet("background-color:White");

ui->GF_21->setText(human->getValueFromFieldForGame(qMakePair(2,1)));
if(ui->GF_21->text()=="O") ui->GF_21->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_21->text()=="X")ui->GF_21->setStyleSheet("background-color:Grey");
else ui->GF_21->setStyleSheet("background-color:White");

ui->GF_22->setText(human->getValueFromFieldForGame(qMakePair(2,2)));
if(ui->GF_22->text()=="O") ui->GF_22->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_22->text()=="X")ui->GF_22->setStyleSheet("background-color:Grey");
else ui->GF_22->setStyleSheet("background-color:White");

ui->GF_23->setText(human->getValueFromFieldForGame(qMakePair(2,3)));
if(ui->GF_23->text()=="O") ui->GF_23->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_23->text()=="X")ui->GF_23->setStyleSheet("background-color:Grey");
else ui->GF_23->setStyleSheet("background-color:White");

ui->GF_24->setText(human->getValueFromFieldForGame(qMakePair(2,4)));
if(ui->GF_24->text()=="O") ui->GF_24->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_24->text()=="X")ui->GF_24->setStyleSheet("background-color:Grey");
else ui->GF_24->setStyleSheet("background-color:White");

ui->GF_25->setText(human->getValueFromFieldForGame(qMakePair(2,5)));
if(ui->GF_25->text()=="O") ui->GF_25->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_25->text()=="X")ui->GF_25->setStyleSheet("background-color:Grey");
else ui->GF_25->setStyleSheet("background-color:White");

ui->GF_26->setText(human->getValueFromFieldForGame(qMakePair(2,6)));
if(ui->GF_26->text()=="O") ui->GF_26->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_26->text()=="X")ui->GF_26->setStyleSheet("background-color:Grey");
else ui->GF_26->setStyleSheet("background-color:White");

ui->GF_27->setText(human->getValueFromFieldForGame(qMakePair(2,7)));
if(ui->GF_27->text()=="O") ui->GF_27->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_27->text()=="X")ui->GF_27->setStyleSheet("background-color:Grey");
else ui->GF_27->setStyleSheet("background-color:White");

ui->GF_28->setText(human->getValueFromFieldForGame(qMakePair(2,8)));
if(ui->GF_28->text()=="O") ui->GF_28->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_28->text()=="X")ui->GF_28->setStyleSheet("background-color:Grey");
else ui->GF_28->setStyleSheet("background-color:White");

ui->GF_29->setText(human->getValueFromFieldForGame(qMakePair(2,9)));
if(ui->GF_29->text()=="O") ui->GF_29->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_29->text()=="X")ui->GF_29->setStyleSheet("background-color:Grey");
else ui->GF_29->setStyleSheet("background-color:White");

ui->GF_30->setText(human->getValueFromFieldForGame(qMakePair(3,0)));
if(ui->GF_30->text()=="O") ui->GF_30->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_30->text()=="X")ui->GF_30->setStyleSheet("background-color:Grey");
else ui->GF_30->setStyleSheet("background-color:White");

ui->GF_31->setText(human->getValueFromFieldForGame(qMakePair(3,1)));
if(ui->GF_31->text()=="O") ui->GF_31->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_31->text()=="X")ui->GF_31->setStyleSheet("background-color:Grey");
else ui->GF_31->setStyleSheet("background-color:White");

ui->GF_32->setText(human->getValueFromFieldForGame(qMakePair(3,2)));
if(ui->GF_32->text()=="O") ui->GF_32->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_32->text()=="X")ui->GF_32->setStyleSheet("background-color:Grey");
else ui->GF_32->setStyleSheet("background-color:White");

ui->GF_33->setText(human->getValueFromFieldForGame(qMakePair(3,3)));
if(ui->GF_33->text()=="O") ui->GF_33->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_33->text()=="X")ui->GF_33->setStyleSheet("background-color:Grey");
else ui->GF_33->setStyleSheet("background-color:White");

ui->GF_34->setText(human->getValueFromFieldForGame(qMakePair(3,4)));
if(ui->GF_34->text()=="O") ui->GF_34->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_34->text()=="X")ui->GF_34->setStyleSheet("background-color:Grey");
else ui->GF_34->setStyleSheet("background-color:White");

ui->GF_35->setText(human->getValueFromFieldForGame(qMakePair(3,5)));
if(ui->GF_35->text()=="O") ui->GF_35->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_35->text()=="X")ui->GF_35->setStyleSheet("background-color:Grey");
else ui->GF_35->setStyleSheet("background-color:White");

ui->GF_36->setText(human->getValueFromFieldForGame(qMakePair(3,6)));
if(ui->GF_36->text()=="O") ui->GF_36->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_36->text()=="X")ui->GF_36->setStyleSheet("background-color:Grey");
else ui->GF_36->setStyleSheet("background-color:White");

ui->GF_37->setText(human->getValueFromFieldForGame(qMakePair(3,7)));
if(ui->GF_37->text()=="O") ui->GF_37->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_37->text()=="X")ui->GF_37->setStyleSheet("background-color:Grey");
else ui->GF_37->setStyleSheet("background-color:White");

ui->GF_38->setText(human->getValueFromFieldForGame(qMakePair(3,8)));
if(ui->GF_38->text()=="O") ui->GF_38->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_38->text()=="X")ui->GF_38->setStyleSheet("background-color:Grey");
else ui->GF_38->setStyleSheet("background-color:White");

ui->GF_39->setText(human->getValueFromFieldForGame(qMakePair(3,9)));
if(ui->GF_39->text()=="O") ui->GF_39->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_39->text()=="X")ui->GF_39->setStyleSheet("background-color:Grey");
else ui->GF_39->setStyleSheet("background-color:White");

ui->GF_40->setText(human->getValueFromFieldForGame(qMakePair(4,0)));
if(ui->GF_40->text()=="O") ui->GF_40->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_40->text()=="X")ui->GF_40->setStyleSheet("background-color:Grey");
else ui->GF_40->setStyleSheet("background-color:White");

ui->GF_41->setText(human->getValueFromFieldForGame(qMakePair(4,1)));
if(ui->GF_41->text()=="O") ui->GF_41->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_41->text()=="X")ui->GF_41->setStyleSheet("background-color:Grey");
else ui->GF_41->setStyleSheet("background-color:White");

ui->GF_42->setText(human->getValueFromFieldForGame(qMakePair(4,2)));
if(ui->GF_42->text()=="O") ui->GF_42->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_42->text()=="X")ui->GF_42->setStyleSheet("background-color:Grey");
else ui->GF_42->setStyleSheet("background-color:White");

ui->GF_43->setText(human->getValueFromFieldForGame(qMakePair(4,3)));
if(ui->GF_43->text()=="O") ui->GF_43->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_43->text()=="X")ui->GF_43->setStyleSheet("background-color:Grey");
else ui->GF_43->setStyleSheet("background-color:White");

ui->GF_44->setText(human->getValueFromFieldForGame(qMakePair(4,4)));
if(ui->GF_44->text()=="O") ui->GF_44->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_44->text()=="X")ui->GF_44->setStyleSheet("background-color:Grey");
else ui->GF_44->setStyleSheet("background-color:White");

ui->GF_45->setText(human->getValueFromFieldForGame(qMakePair(4,5)));
if(ui->GF_45->text()=="O") ui->GF_45->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_45->text()=="X")ui->GF_45->setStyleSheet("background-color:Grey");
else ui->GF_45->setStyleSheet("background-color:White");

ui->GF_46->setText(human->getValueFromFieldForGame(qMakePair(4,6)));
if(ui->GF_46->text()=="O") ui->GF_46->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_46->text()=="X")ui->GF_46->setStyleSheet("background-color:Grey");
else ui->GF_46->setStyleSheet("background-color:White");

ui->GF_47->setText(human->getValueFromFieldForGame(qMakePair(4,7)));
if(ui->GF_47->text()=="O") ui->GF_47->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_47->text()=="X")ui->GF_47->setStyleSheet("background-color:Grey");
else ui->GF_47->setStyleSheet("background-color:White");

ui->GF_48->setText(human->getValueFromFieldForGame(qMakePair(4,8)));
if(ui->GF_48->text()=="O") ui->GF_48->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_48->text()=="X")ui->GF_48->setStyleSheet("background-color:Grey");
else ui->GF_48->setStyleSheet("background-color:White");

ui->GF_49->setText(human->getValueFromFieldForGame(qMakePair(4,9)));
if(ui->GF_49->text()=="O") ui->GF_49->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_49->text()=="X")ui->GF_49->setStyleSheet("background-color:Grey");
else ui->GF_49->setStyleSheet("background-color:White");

ui->GF_50->setText(human->getValueFromFieldForGame(qMakePair(5,0)));
if(ui->GF_50->text()=="O") ui->GF_50->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_50->text()=="X")ui->GF_50->setStyleSheet("background-color:Grey");
else ui->GF_50->setStyleSheet("background-color:White");

ui->GF_51->setText(human->getValueFromFieldForGame(qMakePair(5,1)));
if(ui->GF_51->text()=="O") ui->GF_51->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_51->text()=="X")ui->GF_51->setStyleSheet("background-color:Grey");
else ui->GF_51->setStyleSheet("background-color:White");

ui->GF_52->setText(human->getValueFromFieldForGame(qMakePair(5,2)));
if(ui->GF_52->text()=="O") ui->GF_52->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_52->text()=="X")ui->GF_52->setStyleSheet("background-color:Grey");
else ui->GF_52->setStyleSheet("background-color:White");

ui->GF_53->setText(human->getValueFromFieldForGame(qMakePair(5,3)));
if(ui->GF_53->text()=="O") ui->GF_53->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_53->text()=="X")ui->GF_53->setStyleSheet("background-color:Grey");
else ui->GF_53->setStyleSheet("background-color:White");

ui->GF_54->setText(human->getValueFromFieldForGame(qMakePair(5,4)));
if(ui->GF_54->text()=="O") ui->GF_54->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_54->text()=="X")ui->GF_54->setStyleSheet("background-color:Grey");
else ui->GF_54->setStyleSheet("background-color:White");

ui->GF_55->setText(human->getValueFromFieldForGame(qMakePair(5,5)));
if(ui->GF_55->text()=="O") ui->GF_55->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_55->text()=="X")ui->GF_55->setStyleSheet("background-color:Grey");
else ui->GF_55->setStyleSheet("background-color:White");

ui->GF_56->setText(human->getValueFromFieldForGame(qMakePair(5,6)));
if(ui->GF_56->text()=="O") ui->GF_56->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_56->text()=="X")ui->GF_56->setStyleSheet("background-color:Grey");
else ui->GF_56->setStyleSheet("background-color:White");

ui->GF_57->setText(human->getValueFromFieldForGame(qMakePair(5,7)));
if(ui->GF_57->text()=="O") ui->GF_57->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_57->text()=="X")ui->GF_57->setStyleSheet("background-color:Grey");
else ui->GF_57->setStyleSheet("background-color:White");

ui->GF_58->setText(human->getValueFromFieldForGame(qMakePair(5,8)));
if(ui->GF_58->text()=="O") ui->GF_58->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_58->text()=="X")ui->GF_58->setStyleSheet("background-color:Grey");
else ui->GF_58->setStyleSheet("background-color:White");

ui->GF_59->setText(human->getValueFromFieldForGame(qMakePair(5,9)));
if(ui->GF_59->text()=="O") ui->GF_59->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_59->text()=="X")ui->GF_59->setStyleSheet("background-color:Grey");
else ui->GF_59->setStyleSheet("background-color:White");

ui->GF_60->setText(human->getValueFromFieldForGame(qMakePair(6,0)));
if(ui->GF_60->text()=="O") ui->GF_60->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_60->text()=="X")ui->GF_60->setStyleSheet("background-color:Grey");
else ui->GF_60->setStyleSheet("background-color:White");

ui->GF_61->setText(human->getValueFromFieldForGame(qMakePair(6,1)));
if(ui->GF_61->text()=="O") ui->GF_61->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_61->text()=="X")ui->GF_61->setStyleSheet("background-color:Grey");
else ui->GF_61->setStyleSheet("background-color:White");

ui->GF_62->setText(human->getValueFromFieldForGame(qMakePair(6,2)));
if(ui->GF_62->text()=="O") ui->GF_62->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_62->text()=="X")ui->GF_62->setStyleSheet("background-color:Grey");
else ui->GF_62->setStyleSheet("background-color:White");

ui->GF_63->setText(human->getValueFromFieldForGame(qMakePair(6,3)));
if(ui->GF_63->text()=="O") ui->GF_63->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_63->text()=="X")ui->GF_63->setStyleSheet("background-color:Grey");
else ui->GF_63->setStyleSheet("background-color:White");

ui->GF_64->setText(human->getValueFromFieldForGame(qMakePair(6,4)));
if(ui->GF_64->text()=="O") ui->GF_64->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_64->text()=="X")ui->GF_64->setStyleSheet("background-color:Grey");
else ui->GF_64->setStyleSheet("background-color:White");

ui->GF_65->setText(human->getValueFromFieldForGame(qMakePair(6,5)));
if(ui->GF_65->text()=="O") ui->GF_65->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_65->text()=="X")ui->GF_65->setStyleSheet("background-color:Grey");
else ui->GF_65->setStyleSheet("background-color:White");

ui->GF_66->setText(human->getValueFromFieldForGame(qMakePair(6,6)));
if(ui->GF_66->text()=="O") ui->GF_66->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_66->text()=="X")ui->GF_66->setStyleSheet("background-color:Grey");
else ui->GF_66->setStyleSheet("background-color:White");

ui->GF_67->setText(human->getValueFromFieldForGame(qMakePair(6,7)));
if(ui->GF_67->text()=="O") ui->GF_67->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_67->text()=="X")ui->GF_67->setStyleSheet("background-color:Grey");
else ui->GF_67->setStyleSheet("background-color:White");

ui->GF_68->setText(human->getValueFromFieldForGame(qMakePair(6,8)));
if(ui->GF_68->text()=="O") ui->GF_68->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_68->text()=="X")ui->GF_68->setStyleSheet("background-color:Grey");
else ui->GF_68->setStyleSheet("background-color:White");

ui->GF_69->setText(human->getValueFromFieldForGame(qMakePair(6,9)));
if(ui->GF_69->text()=="O") ui->GF_69->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_69->text()=="X")ui->GF_69->setStyleSheet("background-color:Grey");
else ui->GF_69->setStyleSheet("background-color:White");

ui->GF_70->setText(human->getValueFromFieldForGame(qMakePair(7,0)));
if(ui->GF_70->text()=="O") ui->GF_70->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_70->text()=="X")ui->GF_70->setStyleSheet("background-color:Grey");
else ui->GF_70->setStyleSheet("background-color:White");

ui->GF_71->setText(human->getValueFromFieldForGame(qMakePair(7,1)));
if(ui->GF_71->text()=="O") ui->GF_71->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_71->text()=="X")ui->GF_71->setStyleSheet("background-color:Grey");
else ui->GF_71->setStyleSheet("background-color:White");

ui->GF_72->setText(human->getValueFromFieldForGame(qMakePair(7,2)));
if(ui->GF_72->text()=="O") ui->GF_72->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_72->text()=="X")ui->GF_72->setStyleSheet("background-color:Grey");
else ui->GF_72->setStyleSheet("background-color:White");

ui->GF_73->setText(human->getValueFromFieldForGame(qMakePair(7,3)));
if(ui->GF_73->text()=="O") ui->GF_73->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_73->text()=="X")ui->GF_73->setStyleSheet("background-color:Grey");
else ui->GF_73->setStyleSheet("background-color:White");

ui->GF_74->setText(human->getValueFromFieldForGame(qMakePair(7,4)));
if(ui->GF_74->text()=="O") ui->GF_74->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_74->text()=="X")ui->GF_74->setStyleSheet("background-color:Grey");
else ui->GF_74->setStyleSheet("background-color:White");

ui->GF_75->setText(human->getValueFromFieldForGame(qMakePair(7,5)));
if(ui->GF_75->text()=="O") ui->GF_75->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_75->text()=="X")ui->GF_75->setStyleSheet("background-color:Grey");
else ui->GF_75->setStyleSheet("background-color:White");

ui->GF_76->setText(human->getValueFromFieldForGame(qMakePair(7,6)));
if(ui->GF_76->text()=="O") ui->GF_76->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_76->text()=="X")ui->GF_76->setStyleSheet("background-color:Grey");
else ui->GF_76->setStyleSheet("background-color:White");

ui->GF_77->setText(human->getValueFromFieldForGame(qMakePair(7,7)));
if(ui->GF_77->text()=="O") ui->GF_77->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_77->text()=="X")ui->GF_77->setStyleSheet("background-color:Grey");
else ui->GF_77->setStyleSheet("background-color:White");

ui->GF_78->setText(human->getValueFromFieldForGame(qMakePair(7,8)));
if(ui->GF_78->text()=="O") ui->GF_78->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_78->text()=="X")ui->GF_78->setStyleSheet("background-color:Grey");
else ui->GF_78->setStyleSheet("background-color:White");

ui->GF_79->setText(human->getValueFromFieldForGame(qMakePair(7,9)));
if(ui->GF_79->text()=="O") ui->GF_79->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_79->text()=="X")ui->GF_79->setStyleSheet("background-color:Grey");
else ui->GF_79->setStyleSheet("background-color:White");

ui->GF_80->setText(human->getValueFromFieldForGame(qMakePair(8,0)));
if(ui->GF_80->text()=="O") ui->GF_80->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_80->text()=="X")ui->GF_80->setStyleSheet("background-color:Grey");
else ui->GF_80->setStyleSheet("background-color:White");

ui->GF_81->setText(human->getValueFromFieldForGame(qMakePair(8,1)));
if(ui->GF_81->text()=="O") ui->GF_81->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_81->text()=="X")ui->GF_81->setStyleSheet("background-color:Grey");
else ui->GF_81->setStyleSheet("background-color:White");

ui->GF_82->setText(human->getValueFromFieldForGame(qMakePair(8,2)));
if(ui->GF_82->text()=="O") ui->GF_82->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_82->text()=="X")ui->GF_82->setStyleSheet("background-color:Grey");
else ui->GF_82->setStyleSheet("background-color:White");

ui->GF_83->setText(human->getValueFromFieldForGame(qMakePair(8,3)));
if(ui->GF_83->text()=="O") ui->GF_83->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_83->text()=="X")ui->GF_83->setStyleSheet("background-color:Grey");
else ui->GF_83->setStyleSheet("background-color:White");

ui->GF_84->setText(human->getValueFromFieldForGame(qMakePair(8,4)));
if(ui->GF_84->text()=="O") ui->GF_84->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_84->text()=="X")ui->GF_84->setStyleSheet("background-color:Grey");
else ui->GF_84->setStyleSheet("background-color:White");

ui->GF_85->setText(human->getValueFromFieldForGame(qMakePair(8,5)));
if(ui->GF_85->text()=="O") ui->GF_85->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_85->text()=="X")ui->GF_85->setStyleSheet("background-color:Grey");
else ui->GF_85->setStyleSheet("background-color:White");

ui->GF_86->setText(human->getValueFromFieldForGame(qMakePair(8,6)));
if(ui->GF_86->text()=="O") ui->GF_86->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_86->text()=="X")ui->GF_86->setStyleSheet("background-color:Grey");
else ui->GF_86->setStyleSheet("background-color:White");

ui->GF_87->setText(human->getValueFromFieldForGame(qMakePair(8,7)));
if(ui->GF_87->text()=="O") ui->GF_87->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_87->text()=="X")ui->GF_87->setStyleSheet("background-color:Grey");
else ui->GF_87->setStyleSheet("background-color:White");

ui->GF_88->setText(human->getValueFromFieldForGame(qMakePair(8,8)));
if(ui->GF_88->text()=="O") ui->GF_88->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_88->text()=="X")ui->GF_88->setStyleSheet("background-color:Grey");
else ui->GF_88->setStyleSheet("background-color:White");

ui->GF_89->setText(human->getValueFromFieldForGame(qMakePair(8,9)));
if(ui->GF_89->text()=="O") ui->GF_89->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_89->text()=="X")ui->GF_89->setStyleSheet("background-color:Grey");
else ui->GF_89->setStyleSheet("background-color:White");

ui->GF_90->setText(human->getValueFromFieldForGame(qMakePair(9,0)));
if(ui->GF_90->text()=="O") ui->GF_90->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_90->text()=="X")ui->GF_90->setStyleSheet("background-color:Grey");
else ui->GF_90->setStyleSheet("background-color:White");

ui->GF_91->setText(human->getValueFromFieldForGame(qMakePair(9,1)));
if(ui->GF_91->text()=="O") ui->GF_91->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_91->text()=="X")ui->GF_91->setStyleSheet("background-color:Grey");
else ui->GF_91->setStyleSheet("background-color:White");

ui->GF_92->setText(human->getValueFromFieldForGame(qMakePair(9,2)));
if(ui->GF_92->text()=="O") ui->GF_92->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_92->text()=="X")ui->GF_92->setStyleSheet("background-color:Grey");
else ui->GF_92->setStyleSheet("background-color:White");

ui->GF_93->setText(human->getValueFromFieldForGame(qMakePair(9,3)));
if(ui->GF_93->text()=="O") ui->GF_93->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_93->text()=="X")ui->GF_93->setStyleSheet("background-color:Grey");
else ui->GF_93->setStyleSheet("background-color:White");

ui->GF_94->setText(human->getValueFromFieldForGame(qMakePair(9,4)));
if(ui->GF_94->text()=="O") ui->GF_94->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_94->text()=="X")ui->GF_94->setStyleSheet("background-color:Grey");
else ui->GF_94->setStyleSheet("background-color:White");

ui->GF_95->setText(human->getValueFromFieldForGame(qMakePair(9,5)));
if(ui->GF_95->text()=="O") ui->GF_95->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_95->text()=="X")ui->GF_95->setStyleSheet("background-color:Grey");
else ui->GF_95->setStyleSheet("background-color:White");

ui->GF_96->setText(human->getValueFromFieldForGame(qMakePair(9,6)));
if(ui->GF_96->text()=="O") ui->GF_96->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_96->text()=="X")ui->GF_96->setStyleSheet("background-color:Grey");
else ui->GF_96->setStyleSheet("background-color:White");

ui->GF_97->setText(human->getValueFromFieldForGame(qMakePair(9,7)));
if(ui->GF_97->text()=="O") ui->GF_97->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_97->text()=="X")ui->GF_97->setStyleSheet("background-color:Grey");
else ui->GF_97->setStyleSheet("background-color:White");

ui->GF_98->setText(human->getValueFromFieldForGame(qMakePair(9,8)));
if(ui->GF_98->text()=="O") ui->GF_98->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_98->text()=="X")ui->GF_98->setStyleSheet("background-color:Grey");
else ui->GF_98->setStyleSheet("background-color:White");

ui->GF_99->setText(human->getValueFromFieldForGame(qMakePair(9,9)));
if(ui->GF_99->text()=="O") ui->GF_99->setStyleSheet("background-color:SkyBlue");
else if(ui->GF_99->text()=="X")ui->GF_99->setStyleSheet("background-color:Grey");
else ui->GF_99->setStyleSheet("background-color:White");

}


void GameSeaBattle::SlotPaintToNoteWindow()
{
    ui->NF_00->setText(human->getValueFromFieldForNote(qMakePair(0,0)));
    if(ui->NF_00->text()=="O") ui->NF_00->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_00->text()=="X")ui->NF_00->setStyleSheet("background-color:Grey");
    else ui->NF_00->setStyleSheet("background-color:White");

    ui->NF_01->setText(human->getValueFromFieldForNote(qMakePair(0,1)));
    if(ui->NF_01->text()=="O") ui->NF_01->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_01->text()=="X")ui->NF_01->setStyleSheet("background-color:Grey");
    else ui->NF_01->setStyleSheet("background-color:White");

    ui->NF_02->setText(human->getValueFromFieldForNote(qMakePair(0,2)));
    if(ui->NF_02->text()=="O") ui->NF_02->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_02->text()=="X")ui->NF_02->setStyleSheet("background-color:Grey");
    else ui->NF_02->setStyleSheet("background-color:White");

    ui->NF_03->setText(human->getValueFromFieldForNote(qMakePair(0,3)));
    if(ui->NF_03->text()=="O") ui->NF_03->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_03->text()=="X")ui->NF_03->setStyleSheet("background-color:Grey");
    else ui->NF_03->setStyleSheet("background-color:White");

    ui->NF_04->setText(human->getValueFromFieldForNote(qMakePair(0,4)));
    if(ui->NF_04->text()=="O") ui->NF_04->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_04->text()=="X")ui->NF_04->setStyleSheet("background-color:Grey");
    else ui->NF_04->setStyleSheet("background-color:White");

    ui->NF_05->setText(human->getValueFromFieldForNote(qMakePair(0,5)));
    if(ui->NF_05->text()=="O") ui->NF_05->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_05->text()=="X")ui->NF_05->setStyleSheet("background-color:Grey");
    else ui->NF_05->setStyleSheet("background-color:White");

    ui->NF_06->setText(human->getValueFromFieldForNote(qMakePair(0,6)));
    if(ui->NF_06->text()=="O") ui->NF_06->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_06->text()=="X")ui->NF_06->setStyleSheet("background-color:Grey");
    else ui->NF_06->setStyleSheet("background-color:White");

    ui->NF_07->setText(human->getValueFromFieldForNote(qMakePair(0,7)));
    if(ui->NF_07->text()=="O") ui->NF_07->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_07->text()=="X")ui->NF_07->setStyleSheet("background-color:Grey");
    else ui->NF_07->setStyleSheet("background-color:White");

    ui->NF_08->setText(human->getValueFromFieldForNote(qMakePair(0,8)));
    if(ui->NF_08->text()=="O") ui->NF_08->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_08->text()=="X")ui->NF_08->setStyleSheet("background-color:Grey");
    else ui->NF_08->setStyleSheet("background-color:White");

    ui->NF_09->setText(human->getValueFromFieldForNote(qMakePair(0,9)));
    if(ui->NF_09->text()=="O") ui->NF_09->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_09->text()=="X")ui->NF_09->setStyleSheet("background-color:Grey");
    else ui->NF_09->setStyleSheet("background-color:White");

    ui->NF_10->setText(human->getValueFromFieldForNote(qMakePair(1,0)));
    if(ui->NF_10->text()=="O") ui->NF_10->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_10->text()=="X")ui->NF_10->setStyleSheet("background-color:Grey");
    else ui->NF_10->setStyleSheet("background-color:White");

    ui->NF_11->setText(human->getValueFromFieldForNote(qMakePair(1,1)));
    if(ui->NF_11->text()=="O") ui->NF_11->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_11->text()=="X")ui->NF_11->setStyleSheet("background-color:Grey");
    else ui->NF_11->setStyleSheet("background-color:White");

    ui->NF_12->setText(human->getValueFromFieldForNote(qMakePair(1,2)));
    if(ui->NF_12->text()=="O") ui->NF_12->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_12->text()=="X")ui->NF_12->setStyleSheet("background-color:Grey");
    else ui->NF_12->setStyleSheet("background-color:White");

    ui->NF_13->setText(human->getValueFromFieldForNote(qMakePair(1,3)));
    if(ui->NF_13->text()=="O") ui->NF_13->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_13->text()=="X")ui->NF_13->setStyleSheet("background-color:Grey");
    else ui->NF_13->setStyleSheet("background-color:White");

    ui->NF_14->setText(human->getValueFromFieldForNote(qMakePair(1,4)));
    if(ui->NF_14->text()=="O") ui->NF_14->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_14->text()=="X")ui->NF_14->setStyleSheet("background-color:Grey");
    else ui->NF_14->setStyleSheet("background-color:White");

    ui->NF_15->setText(human->getValueFromFieldForNote(qMakePair(1,5)));
    if(ui->NF_15->text()=="O") ui->NF_15->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_15->text()=="X")ui->NF_15->setStyleSheet("background-color:Grey");
    else ui->NF_15->setStyleSheet("background-color:White");

    ui->NF_16->setText(human->getValueFromFieldForNote(qMakePair(1,6)));
    if(ui->NF_16->text()=="O") ui->NF_16->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_16->text()=="X")ui->NF_16->setStyleSheet("background-color:Grey");
    else ui->NF_16->setStyleSheet("background-color:White");

    ui->NF_17->setText(human->getValueFromFieldForNote(qMakePair(1,7)));
    if(ui->NF_17->text()=="O") ui->NF_17->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_17->text()=="X")ui->NF_17->setStyleSheet("background-color:Grey");
    else ui->NF_17->setStyleSheet("background-color:White");

    ui->NF_18->setText(human->getValueFromFieldForNote(qMakePair(1,8)));
    if(ui->NF_18->text()=="O") ui->NF_18->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_18->text()=="X")ui->NF_18->setStyleSheet("background-color:Grey");
    else ui->NF_18->setStyleSheet("background-color:White");

    ui->NF_19->setText(human->getValueFromFieldForNote(qMakePair(1,9)));
    if(ui->NF_19->text()=="O") ui->NF_19->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_19->text()=="X")ui->NF_19->setStyleSheet("background-color:Grey");
    else ui->NF_19->setStyleSheet("background-color:White");

    ui->NF_20->setText(human->getValueFromFieldForNote(qMakePair(2,0)));
    if(ui->NF_20->text()=="O") ui->NF_20->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_20->text()=="X")ui->NF_20->setStyleSheet("background-color:Grey");
    else ui->NF_20->setStyleSheet("background-color:White");

    ui->NF_21->setText(human->getValueFromFieldForNote(qMakePair(2,1)));
    if(ui->NF_21->text()=="O") ui->NF_21->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_21->text()=="X")ui->NF_21->setStyleSheet("background-color:Grey");
    else ui->NF_21->setStyleSheet("background-color:White");

    ui->NF_22->setText(human->getValueFromFieldForNote(qMakePair(2,2)));
    if(ui->NF_22->text()=="O") ui->NF_22->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_22->text()=="X")ui->NF_22->setStyleSheet("background-color:Grey");
    else ui->NF_22->setStyleSheet("background-color:White");

    ui->NF_23->setText(human->getValueFromFieldForNote(qMakePair(2,3)));
    if(ui->NF_23->text()=="O") ui->NF_23->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_23->text()=="X")ui->NF_23->setStyleSheet("background-color:Grey");
    else ui->NF_23->setStyleSheet("background-color:White");

    ui->NF_24->setText(human->getValueFromFieldForNote(qMakePair(2,4)));
    if(ui->NF_24->text()=="O") ui->NF_24->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_24->text()=="X")ui->NF_24->setStyleSheet("background-color:Grey");
    else ui->NF_24->setStyleSheet("background-color:White");

    ui->NF_25->setText(human->getValueFromFieldForNote(qMakePair(2,5)));
    if(ui->NF_25->text()=="O") ui->NF_25->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_25->text()=="X")ui->NF_25->setStyleSheet("background-color:Grey");
    else ui->NF_25->setStyleSheet("background-color:White");

    ui->NF_26->setText(human->getValueFromFieldForNote(qMakePair(2,6)));
    if(ui->NF_26->text()=="O") ui->NF_26->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_26->text()=="X")ui->NF_26->setStyleSheet("background-color:Grey");
    else ui->NF_26->setStyleSheet("background-color:White");

    ui->NF_27->setText(human->getValueFromFieldForNote(qMakePair(2,7)));
    if(ui->NF_27->text()=="O") ui->NF_27->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_27->text()=="X")ui->NF_27->setStyleSheet("background-color:Grey");
    else ui->NF_27->setStyleSheet("background-color:White");

    ui->NF_28->setText(human->getValueFromFieldForNote(qMakePair(2,8)));
    if(ui->NF_28->text()=="O") ui->NF_28->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_28->text()=="X")ui->NF_28->setStyleSheet("background-color:Grey");
    else ui->NF_28->setStyleSheet("background-color:White");

    ui->NF_29->setText(human->getValueFromFieldForNote(qMakePair(2,9)));
    if(ui->NF_29->text()=="O") ui->NF_29->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_29->text()=="X")ui->NF_29->setStyleSheet("background-color:Grey");
    else ui->NF_29->setStyleSheet("background-color:White");

    ui->NF_30->setText(human->getValueFromFieldForNote(qMakePair(3,0)));
    if(ui->NF_30->text()=="O") ui->NF_30->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_30->text()=="X")ui->NF_30->setStyleSheet("background-color:Grey");
    else ui->NF_30->setStyleSheet("background-color:White");

    ui->NF_31->setText(human->getValueFromFieldForNote(qMakePair(3,1)));
    if(ui->NF_31->text()=="O") ui->NF_31->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_31->text()=="X")ui->NF_31->setStyleSheet("background-color:Grey");
    else ui->NF_31->setStyleSheet("background-color:White");

    ui->NF_32->setText(human->getValueFromFieldForNote(qMakePair(3,2)));
    if(ui->NF_32->text()=="O") ui->NF_32->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_32->text()=="X")ui->NF_32->setStyleSheet("background-color:Grey");
    else ui->NF_32->setStyleSheet("background-color:White");

    ui->NF_33->setText(human->getValueFromFieldForNote(qMakePair(3,3)));
    if(ui->NF_33->text()=="O") ui->NF_33->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_33->text()=="X")ui->NF_33->setStyleSheet("background-color:Grey");
    else ui->NF_33->setStyleSheet("background-color:White");

    ui->NF_34->setText(human->getValueFromFieldForNote(qMakePair(3,4)));
    if(ui->NF_34->text()=="O") ui->NF_34->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_34->text()=="X")ui->NF_34->setStyleSheet("background-color:Grey");
    else ui->NF_34->setStyleSheet("background-color:White");

    ui->NF_35->setText(human->getValueFromFieldForNote(qMakePair(3,5)));
    if(ui->NF_35->text()=="O") ui->NF_35->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_35->text()=="X")ui->NF_35->setStyleSheet("background-color:Grey");
    else ui->NF_35->setStyleSheet("background-color:White");

    ui->NF_36->setText(human->getValueFromFieldForNote(qMakePair(3,6)));
    if(ui->NF_36->text()=="O") ui->NF_36->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_36->text()=="X")ui->NF_36->setStyleSheet("background-color:Grey");
    else ui->NF_36->setStyleSheet("background-color:White");

    ui->NF_37->setText(human->getValueFromFieldForNote(qMakePair(3,7)));
    if(ui->NF_37->text()=="O") ui->NF_37->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_37->text()=="X")ui->NF_37->setStyleSheet("background-color:Grey");
    else ui->NF_37->setStyleSheet("background-color:White");

    ui->NF_38->setText(human->getValueFromFieldForNote(qMakePair(3,8)));
    if(ui->NF_38->text()=="O") ui->NF_38->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_38->text()=="X")ui->NF_38->setStyleSheet("background-color:Grey");
    else ui->NF_38->setStyleSheet("background-color:White");

    ui->NF_39->setText(human->getValueFromFieldForNote(qMakePair(3,9)));
    if(ui->NF_39->text()=="O") ui->NF_39->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_39->text()=="X")ui->NF_39->setStyleSheet("background-color:Grey");
    else ui->NF_39->setStyleSheet("background-color:White");

    ui->NF_40->setText(human->getValueFromFieldForNote(qMakePair(4,0)));
    if(ui->NF_40->text()=="O") ui->NF_40->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_40->text()=="X")ui->NF_40->setStyleSheet("background-color:Grey");
    else ui->NF_40->setStyleSheet("background-color:White");

    ui->NF_41->setText(human->getValueFromFieldForNote(qMakePair(4,1)));
    if(ui->NF_41->text()=="O") ui->NF_41->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_41->text()=="X")ui->NF_41->setStyleSheet("background-color:Grey");
    else ui->NF_41->setStyleSheet("background-color:White");

    ui->NF_42->setText(human->getValueFromFieldForNote(qMakePair(4,2)));
    if(ui->NF_42->text()=="O") ui->NF_42->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_42->text()=="X")ui->NF_42->setStyleSheet("background-color:Grey");
    else ui->NF_42->setStyleSheet("background-color:White");

    ui->NF_43->setText(human->getValueFromFieldForNote(qMakePair(4,3)));
    if(ui->NF_43->text()=="O") ui->NF_43->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_43->text()=="X")ui->NF_43->setStyleSheet("background-color:Grey");
    else ui->NF_43->setStyleSheet("background-color:White");

    ui->NF_44->setText(human->getValueFromFieldForNote(qMakePair(4,4)));
    if(ui->NF_44->text()=="O") ui->NF_44->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_44->text()=="X")ui->NF_44->setStyleSheet("background-color:Grey");
    else ui->NF_44->setStyleSheet("background-color:White");

    ui->NF_45->setText(human->getValueFromFieldForNote(qMakePair(4,5)));
    if(ui->NF_45->text()=="O") ui->NF_45->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_45->text()=="X")ui->NF_45->setStyleSheet("background-color:Grey");
    else ui->NF_45->setStyleSheet("background-color:White");

    ui->NF_46->setText(human->getValueFromFieldForNote(qMakePair(4,6)));
    if(ui->NF_46->text()=="O") ui->NF_46->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_46->text()=="X")ui->NF_46->setStyleSheet("background-color:Grey");
    else ui->NF_46->setStyleSheet("background-color:White");

    ui->NF_47->setText(human->getValueFromFieldForNote(qMakePair(4,7)));
    if(ui->NF_47->text()=="O") ui->NF_47->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_47->text()=="X")ui->NF_47->setStyleSheet("background-color:Grey");
    else ui->NF_47->setStyleSheet("background-color:White");

    ui->NF_48->setText(human->getValueFromFieldForNote(qMakePair(4,8)));
    if(ui->NF_48->text()=="O") ui->NF_48->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_48->text()=="X")ui->NF_48->setStyleSheet("background-color:Grey");
    else ui->NF_48->setStyleSheet("background-color:White");

    ui->NF_49->setText(human->getValueFromFieldForNote(qMakePair(4,9)));
    if(ui->NF_49->text()=="O") ui->NF_49->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_49->text()=="X")ui->NF_49->setStyleSheet("background-color:Grey");
    else ui->NF_49->setStyleSheet("background-color:White");

    ui->NF_50->setText(human->getValueFromFieldForNote(qMakePair(5,0)));
    if(ui->NF_50->text()=="O") ui->NF_50->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_50->text()=="X")ui->NF_50->setStyleSheet("background-color:Grey");
    else ui->NF_50->setStyleSheet("background-color:White");

    ui->NF_51->setText(human->getValueFromFieldForNote(qMakePair(5,1)));
    if(ui->NF_51->text()=="O") ui->NF_51->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_51->text()=="X")ui->NF_51->setStyleSheet("background-color:Grey");
    else ui->NF_51->setStyleSheet("background-color:White");

    ui->NF_52->setText(human->getValueFromFieldForNote(qMakePair(5,2)));
    if(ui->NF_52->text()=="O") ui->NF_52->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_52->text()=="X")ui->NF_52->setStyleSheet("background-color:Grey");
    else ui->NF_52->setStyleSheet("background-color:White");

    ui->NF_53->setText(human->getValueFromFieldForNote(qMakePair(5,3)));
    if(ui->NF_53->text()=="O") ui->NF_53->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_53->text()=="X")ui->NF_53->setStyleSheet("background-color:Grey");
    else ui->NF_53->setStyleSheet("background-color:White");

    ui->NF_54->setText(human->getValueFromFieldForNote(qMakePair(5,4)));
    if(ui->NF_54->text()=="O") ui->NF_54->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_54->text()=="X")ui->NF_54->setStyleSheet("background-color:Grey");
    else ui->NF_54->setStyleSheet("background-color:White");

    ui->NF_55->setText(human->getValueFromFieldForNote(qMakePair(5,5)));
    if(ui->NF_55->text()=="O") ui->NF_55->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_55->text()=="X")ui->NF_55->setStyleSheet("background-color:Grey");
    else ui->NF_55->setStyleSheet("background-color:White");

    ui->NF_56->setText(human->getValueFromFieldForNote(qMakePair(5,6)));
    if(ui->NF_56->text()=="O") ui->NF_56->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_56->text()=="X")ui->NF_56->setStyleSheet("background-color:Grey");
    else ui->NF_56->setStyleSheet("background-color:White");

    ui->NF_57->setText(human->getValueFromFieldForNote(qMakePair(5,7)));
    if(ui->NF_57->text()=="O") ui->NF_57->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_57->text()=="X")ui->NF_57->setStyleSheet("background-color:Grey");
    else ui->NF_57->setStyleSheet("background-color:White");

    ui->NF_58->setText(human->getValueFromFieldForNote(qMakePair(5,8)));
    if(ui->NF_58->text()=="O") ui->NF_58->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_58->text()=="X")ui->NF_58->setStyleSheet("background-color:Grey");
    else ui->NF_58->setStyleSheet("background-color:White");

    ui->NF_59->setText(human->getValueFromFieldForNote(qMakePair(5,9)));
    if(ui->NF_59->text()=="O") ui->NF_59->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_59->text()=="X")ui->NF_59->setStyleSheet("background-color:Grey");
    else ui->NF_59->setStyleSheet("background-color:White");

    ui->NF_60->setText(human->getValueFromFieldForNote(qMakePair(6,0)));
    if(ui->NF_60->text()=="O") ui->NF_60->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_60->text()=="X")ui->NF_60->setStyleSheet("background-color:Grey");
    else ui->NF_60->setStyleSheet("background-color:White");

    ui->NF_61->setText(human->getValueFromFieldForNote(qMakePair(6,1)));
    if(ui->NF_61->text()=="O") ui->NF_61->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_61->text()=="X")ui->NF_61->setStyleSheet("background-color:Grey");
    else ui->NF_61->setStyleSheet("background-color:White");

    ui->NF_62->setText(human->getValueFromFieldForNote(qMakePair(6,2)));
    if(ui->NF_62->text()=="O") ui->NF_62->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_62->text()=="X")ui->NF_62->setStyleSheet("background-color:Grey");
    else ui->NF_62->setStyleSheet("background-color:White");

    ui->NF_63->setText(human->getValueFromFieldForNote(qMakePair(6,3)));
    if(ui->NF_63->text()=="O") ui->NF_63->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_63->text()=="X")ui->NF_63->setStyleSheet("background-color:Grey");
    else ui->NF_63->setStyleSheet("background-color:White");

    ui->NF_64->setText(human->getValueFromFieldForNote(qMakePair(6,4)));
    if(ui->NF_64->text()=="O") ui->NF_64->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_64->text()=="X")ui->NF_64->setStyleSheet("background-color:Grey");
    else ui->NF_64->setStyleSheet("background-color:White");

    ui->NF_65->setText(human->getValueFromFieldForNote(qMakePair(6,5)));
    if(ui->NF_65->text()=="O") ui->NF_65->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_65->text()=="X")ui->NF_65->setStyleSheet("background-color:Grey");
    else ui->NF_65->setStyleSheet("background-color:White");

    ui->NF_66->setText(human->getValueFromFieldForNote(qMakePair(6,6)));
    if(ui->NF_66->text()=="O") ui->NF_66->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_66->text()=="X")ui->NF_66->setStyleSheet("background-color:Grey");
    else ui->NF_66->setStyleSheet("background-color:White");

    ui->NF_67->setText(human->getValueFromFieldForNote(qMakePair(6,7)));
    if(ui->NF_67->text()=="O") ui->NF_67->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_67->text()=="X")ui->NF_67->setStyleSheet("background-color:Grey");
    else ui->NF_67->setStyleSheet("background-color:White");

    ui->NF_68->setText(human->getValueFromFieldForNote(qMakePair(6,8)));
    if(ui->NF_68->text()=="O") ui->NF_68->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_68->text()=="X")ui->NF_68->setStyleSheet("background-color:Grey");
    else ui->NF_68->setStyleSheet("background-color:White");

    ui->NF_69->setText(human->getValueFromFieldForNote(qMakePair(6,9)));
    if(ui->NF_69->text()=="O") ui->NF_69->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_69->text()=="X")ui->NF_69->setStyleSheet("background-color:Grey");
    else ui->NF_69->setStyleSheet("background-color:White");

    ui->NF_70->setText(human->getValueFromFieldForNote(qMakePair(7,0)));
    if(ui->NF_70->text()=="O") ui->NF_70->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_70->text()=="X")ui->NF_70->setStyleSheet("background-color:Grey");
    else ui->NF_70->setStyleSheet("background-color:White");

    ui->NF_71->setText(human->getValueFromFieldForNote(qMakePair(7,1)));
    if(ui->NF_71->text()=="O") ui->NF_71->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_71->text()=="X")ui->NF_71->setStyleSheet("background-color:Grey");
    else ui->NF_71->setStyleSheet("background-color:White");

    ui->NF_72->setText(human->getValueFromFieldForNote(qMakePair(7,2)));
    if(ui->NF_72->text()=="O") ui->NF_72->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_72->text()=="X")ui->NF_72->setStyleSheet("background-color:Grey");
    else ui->NF_72->setStyleSheet("background-color:White");

    ui->NF_73->setText(human->getValueFromFieldForNote(qMakePair(7,3)));
    if(ui->NF_73->text()=="O") ui->NF_73->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_73->text()=="X")ui->NF_73->setStyleSheet("background-color:Grey");
    else ui->NF_73->setStyleSheet("background-color:White");

    ui->NF_74->setText(human->getValueFromFieldForNote(qMakePair(7,4)));
    if(ui->NF_74->text()=="O") ui->NF_74->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_74->text()=="X")ui->NF_74->setStyleSheet("background-color:Grey");
    else ui->NF_74->setStyleSheet("background-color:White");

    ui->NF_75->setText(human->getValueFromFieldForNote(qMakePair(7,5)));
    if(ui->NF_75->text()=="O") ui->NF_75->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_75->text()=="X")ui->NF_75->setStyleSheet("background-color:Grey");
    else ui->NF_75->setStyleSheet("background-color:White");

    ui->NF_76->setText(human->getValueFromFieldForNote(qMakePair(7,6)));
    if(ui->NF_76->text()=="O") ui->NF_76->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_76->text()=="X")ui->NF_76->setStyleSheet("background-color:Grey");
    else ui->NF_76->setStyleSheet("background-color:White");

    ui->NF_77->setText(human->getValueFromFieldForNote(qMakePair(7,7)));
    if(ui->NF_77->text()=="O") ui->NF_77->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_77->text()=="X")ui->NF_77->setStyleSheet("background-color:Grey");
    else ui->NF_77->setStyleSheet("background-color:White");

    ui->NF_78->setText(human->getValueFromFieldForNote(qMakePair(7,8)));
    if(ui->NF_78->text()=="O") ui->NF_78->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_78->text()=="X")ui->NF_78->setStyleSheet("background-color:Grey");
    else ui->NF_78->setStyleSheet("background-color:White");

    ui->NF_79->setText(human->getValueFromFieldForNote(qMakePair(7,9)));
    if(ui->NF_79->text()=="O") ui->NF_79->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_79->text()=="X")ui->NF_79->setStyleSheet("background-color:Grey");
    else ui->NF_79->setStyleSheet("background-color:White");

    ui->NF_80->setText(human->getValueFromFieldForNote(qMakePair(8,0)));
    if(ui->NF_80->text()=="O") ui->NF_80->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_80->text()=="X")ui->NF_80->setStyleSheet("background-color:Grey");
    else ui->NF_80->setStyleSheet("background-color:White");

    ui->NF_81->setText(human->getValueFromFieldForNote(qMakePair(8,1)));
    if(ui->NF_81->text()=="O") ui->NF_81->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_81->text()=="X")ui->NF_81->setStyleSheet("background-color:Grey");
    else ui->NF_81->setStyleSheet("background-color:White");

    ui->NF_82->setText(human->getValueFromFieldForNote(qMakePair(8,2)));
    if(ui->NF_82->text()=="O") ui->NF_82->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_82->text()=="X")ui->NF_82->setStyleSheet("background-color:Grey");
    else ui->NF_82->setStyleSheet("background-color:White");

    ui->NF_83->setText(human->getValueFromFieldForNote(qMakePair(8,3)));
    if(ui->NF_83->text()=="O") ui->NF_83->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_83->text()=="X")ui->NF_83->setStyleSheet("background-color:Grey");
    else ui->NF_83->setStyleSheet("background-color:White");

    ui->NF_84->setText(human->getValueFromFieldForNote(qMakePair(8,4)));
    if(ui->NF_84->text()=="O") ui->NF_84->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_84->text()=="X")ui->NF_84->setStyleSheet("background-color:Grey");
    else ui->NF_84->setStyleSheet("background-color:White");

    ui->NF_85->setText(human->getValueFromFieldForNote(qMakePair(8,5)));
    if(ui->NF_85->text()=="O") ui->NF_85->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_85->text()=="X")ui->NF_85->setStyleSheet("background-color:Grey");
    else ui->NF_85->setStyleSheet("background-color:White");

    ui->NF_86->setText(human->getValueFromFieldForNote(qMakePair(8,6)));
    if(ui->NF_86->text()=="O") ui->NF_86->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_86->text()=="X")ui->NF_86->setStyleSheet("background-color:Grey");
    else ui->NF_86->setStyleSheet("background-color:White");

    ui->NF_87->setText(human->getValueFromFieldForNote(qMakePair(8,7)));
    if(ui->NF_87->text()=="O") ui->NF_87->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_87->text()=="X")ui->NF_87->setStyleSheet("background-color:Grey");
    else ui->NF_87->setStyleSheet("background-color:White");

    ui->NF_88->setText(human->getValueFromFieldForNote(qMakePair(8,8)));
    if(ui->NF_88->text()=="O") ui->NF_88->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_88->text()=="X")ui->NF_88->setStyleSheet("background-color:Grey");
    else ui->NF_88->setStyleSheet("background-color:White");

    ui->NF_89->setText(human->getValueFromFieldForNote(qMakePair(8,9)));
    if(ui->NF_89->text()=="O") ui->NF_89->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_89->text()=="X")ui->NF_89->setStyleSheet("background-color:Grey");
    else ui->NF_89->setStyleSheet("background-color:White");

    ui->NF_90->setText(human->getValueFromFieldForNote(qMakePair(9,0)));
    if(ui->NF_90->text()=="O") ui->NF_90->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_90->text()=="X")ui->NF_90->setStyleSheet("background-color:Grey");
    else ui->NF_90->setStyleSheet("background-color:White");

    ui->NF_91->setText(human->getValueFromFieldForNote(qMakePair(9,1)));
    if(ui->NF_91->text()=="O") ui->NF_91->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_91->text()=="X")ui->NF_91->setStyleSheet("background-color:Grey");
    else ui->NF_91->setStyleSheet("background-color:White");

    ui->NF_92->setText(human->getValueFromFieldForNote(qMakePair(9,2)));
    if(ui->NF_92->text()=="O") ui->NF_92->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_92->text()=="X")ui->NF_92->setStyleSheet("background-color:Grey");
    else ui->NF_92->setStyleSheet("background-color:White");

    ui->NF_93->setText(human->getValueFromFieldForNote(qMakePair(9,3)));
    if(ui->NF_93->text()=="O") ui->NF_93->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_93->text()=="X")ui->NF_93->setStyleSheet("background-color:Grey");
    else ui->NF_93->setStyleSheet("background-color:White");

    ui->NF_94->setText(human->getValueFromFieldForNote(qMakePair(9,4)));
    if(ui->NF_94->text()=="O") ui->NF_94->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_94->text()=="X")ui->NF_94->setStyleSheet("background-color:Grey");
    else ui->NF_94->setStyleSheet("background-color:White");

    ui->NF_95->setText(human->getValueFromFieldForNote(qMakePair(9,5)));
    if(ui->NF_95->text()=="O") ui->NF_95->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_95->text()=="X")ui->NF_95->setStyleSheet("background-color:Grey");
    else ui->NF_95->setStyleSheet("background-color:White");

    ui->NF_96->setText(human->getValueFromFieldForNote(qMakePair(9,6)));
    if(ui->NF_96->text()=="O") ui->NF_96->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_96->text()=="X")ui->NF_96->setStyleSheet("background-color:Grey");
    else ui->NF_96->setStyleSheet("background-color:White");

    ui->NF_97->setText(human->getValueFromFieldForNote(qMakePair(9,7)));
    if(ui->NF_97->text()=="O") ui->NF_97->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_97->text()=="X")ui->NF_97->setStyleSheet("background-color:Grey");
    else ui->NF_97->setStyleSheet("background-color:White");

    ui->NF_98->setText(human->getValueFromFieldForNote(qMakePair(9,8)));
    if(ui->NF_98->text()=="O") ui->NF_98->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_98->text()=="X")ui->NF_98->setStyleSheet("background-color:Grey");
    else ui->NF_98->setStyleSheet("background-color:White");

    ui->NF_99->setText(human->getValueFromFieldForNote(qMakePair(9,9)));
    if(ui->NF_99->text()=="O") ui->NF_99->setStyleSheet("background-color:SkyBlue");
    else if(ui->NF_99->text()=="X")ui->NF_99->setStyleSheet("background-color:Grey");
    else ui->NF_99->setStyleSheet("background-color:White");
}
GameSeaBattle::~GameSeaBattle()
{
delete ui;
}


