#include <QMainWindow>

#include "engine/CDriver.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    QMainWindow qmw;
    CDriver d(&qmw);
    
    qmw.show();
    d.startGame();
    
    return a.exec();
}
