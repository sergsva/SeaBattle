#ifndef GAMESEABATTLE_H
#define GAMESEABATTLE_H
#include"inputwindow.h"
#include"humanplayer.h"
#include"smartplayer.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class GameSeaBattle : public QMainWindow
{
    Q_OBJECT

public:
  bool gameStart;
  explicit GameSeaBattle(QWidget *parent = 0);

    ~GameSeaBattle();

public slots:
    void SlotClickNewGame();
    void SlotHideInterface();
    void SlotSetFirstStepPlayer();
    void SlotSetFirstStepPC();
    void SlotSetAutoFillField();
    void SlotSetManFillField();
    void SlotPaintToMainWindow();
     void SlotPaintToNoteWindow();
    void SlotRecFromFormToPlayer();
    void SlotClickNewBattle();
 void SlotAfterShoot();

signals:
    void SignalViewPlayerField();

private slots:


private:
    Ui::MainWindow * ui;
    void setInfoToLabelText(const QString& str);
    InputWindow* inputWnd;
    HumanPlayer* human;
    SmartPlayer* pc;
    int queueShooting;


};

#endif // GAMESEABATTLE_H

