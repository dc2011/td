#include <QMainWindow>

#include "SDriver.h"

int main(int argc, char **argv) {
    QCoreApplication a(argc, argv);
    SDriver d;
    
    d.startGame();
    
    return a.exec();
}
