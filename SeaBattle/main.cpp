#include "gameseabattle.h"
#include"field.h"
#include"time.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    std::srand(time(0));
    QApplication app(argc, argv);
    GameSeaBattle newGame;
    newGame.show();

    return app.exec();
}
