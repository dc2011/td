#include <QMainWindow>

#include "engine/CDriver.h"

int main(int argc, char **argv) {
    CDriver d(argc, argv);
    QMainWindow qmw;
    qmw.show();
    d.startGame();
    
    return d.exec();
}
