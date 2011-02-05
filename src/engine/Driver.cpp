#include <QtGui>
#include <QWidget>
#include <QTimer>
#include <QApplication>
#include <QVector>
#include "gameinfo.h"
#include "gameobject.h"
#include "driver.h"

Driver::Driver(int argc, char** argv):QApplication(argc, argv) {

}
void Driver::bindAll() {

}

void Driver::startGame() {
    Driver::gameTimer.start(30);
}

void Driver::endGame() {
    Driver::gameTimer.stop();
    //cleanup code
}
