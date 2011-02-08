//<<<<<<< HEAD
//#include <QMainWindow>
//#include <QGraphicsScene>
//#include <QGraphicsView>
//#include "engine/CDriver.h"
//#include "graphics/mapdisplayer.h"

//int main(int argc, char **argv) {
//    QApplication a(argc, argv);
//    QMainWindow qmw;
//    CDriver d(&qmw);
//    QGraphicsScene gs;
//    QGraphicsView mapview(&gs);
//    MapDisplayer map(&gs);
//    map.viewMap(QString("../maps/sewers.tmx"));
//    //qmw.setCentralWidget(&gs);
//    mapview.show();
//    //qmw.show();
//    d.startGame();
    
//    return a.exec();
//}
//=======
#include <QObject>
#include <QApplication>
#include "MainWindow.h"
#include "util/thread.h"

#include "engine/CDriver.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    td::MainWindow qmw;
    td::CDriver clientDriver(&qmw);
    td::Thread* driverThread = new td::Thread();
    
    QObject::connect(driverThread, SIGNAL(started()), &clientDriver, SLOT(startGame()));
    clientDriver.moveToThread(driverThread);

    driverThread->start();
    qmw.show();
    
    return a.exec();
}

