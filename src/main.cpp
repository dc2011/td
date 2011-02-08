#include <QObject>
#include <QApplication>
#include "MainWindow.h"
#include "util/thread.h"
#include "graphics/mapdisplayer.h"
#include "engine/CDriver.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    td::MainWindow qmw;
    td::CDriver clientDriver(&qmw);
    td::Thread* driverThread = new td::Thread();
    
    QObject::connect(driverThread, SIGNAL(started()), &clientDriver, SLOT(startGame()));
    clientDriver.moveToThread(driverThread);

    driverThread->start();
    // Construct a map
    MapDisplayer map(qmw.getScene());
    // Show the map
    map.viewMap(QString("../maps/sewers.tmx"));
    qmw.show();
    
    return a.exec();
}

