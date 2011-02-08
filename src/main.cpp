#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "engine/CDriver.h"
#include "graphics/mapdisplayer.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    QMainWindow qmw;
    CDriver d(&qmw);
    QGraphicsScene gs;
    QGraphicsView mapview(&gs);
    MapDisplayer map(&gs);
    map.viewMap(QString("../maps/sewers.tmx"));
    //qmw.setCentralWidget(&gs);
    mapview.show();
    //qmw.show();
    d.startGame();
    
    return a.exec();
}
