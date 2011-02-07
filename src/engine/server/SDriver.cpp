#include <QtGui>
#include <QTimer>
#include <QApplication>
#include <QVector>
#include <QWidget>
#include "SDriver.h"

SDriver::SDriver() {
    SDriver::gameTimer_ = new QTimer(this);
}

SDriver::~SDriver() {
    delete SDriver::gameTimer_;
}


//void SDriver::bindAll() {
   // QVector<GameObject>::iterator it;
    //for(it = SDriver::objects.begin(); it != SDriver::objects.end(); ++it) {
       // bindSingle(*it);
    //}
//}

//void SDriver::bindSingle(const GameObject& obj) {
  //  connect(&SDriver::gameTimer_, SIGNAL(timeout()), obj, SLOT(update()));
//}

void SDriver::startGame() {
    SDriver::gameTimer_ -> start(30);
}

void SDriver::endGame() {
    SDriver::gameTimer_ -> stop();
    //cleanup code
}

//int SDriver::loadMap(char* map) {
    //open map file, parse all map data, create map object,
    //create tiles and stuff, store everything in map object, store map object
    //in gameinfo.

    //return false on any type of failure,
    //return true on success
//}
