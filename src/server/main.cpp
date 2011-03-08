#include <QMainWindow>

#include "../engine/SDriver.h"

int main(int argc, char **argv) {
    QCoreApplication a(argc, argv);
    td::SDriver d;
    
    d.startGame();
    
    return a.exec();
}
