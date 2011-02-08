#include <QObject>
#include <QThread>
#include <QApplication>
#include "MainWindow.h"

#include "engine/CDriver.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    td::MainWindow qmw;
    td::CDriver clientDriver(&qmw);
    QThread driverThread;
    
    QObject::connect(&driverThread, SIGNAL(started()), &clientDriver, SLOT(startGame()));
    clientDriver.moveToThread(&driverThread);

    driverThread.start();
    qmw.show();
    
    return a.exec();
}
