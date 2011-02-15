#include <QObject>
#include <QApplication>
#include "MainWindow.h"
#include "../util/thread.h"
#include "../graphics/mapdisplayer.h"
#include "../engine/CDriver.h"
#include "../audio/manager.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    td::MainWindow qmw;
    td::CDriver clientDriver(&qmw);
    td::Thread* driverThread = new td::Thread();
    QQueue<QString> musicList = td::AudioManager::instance()->musicDir("../sound/music/");
    td::AudioManager::instance();

    QObject::connect(driverThread, SIGNAL(started()), &clientDriver, SLOT(startGame()));
    clientDriver.moveToThread(driverThread);

    driverThread->start();
    td::AudioManager::instance()->playMusic(musicList);
    // Construct a map
    /*MapDisplayer map(qmw.getScene());
    // Show the map
    map.viewMap(QString("../maps/desert.tmx"));*/
    qmw.show();

    
    
    return a.exec();
}

