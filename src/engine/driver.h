#ifndef DRIVER_H
#define DRIVER_H
#include <QtGui> 
#include <QWidget>
#include <QTimer>
#include <QApplication>
#include <QVector>
#include "gameinfo.h"
#include "gameobject.h"
class Driver : public QApplication {
  
 private:
  GameInfo gameInfo;
  QTimer gameTimer;
  QVector<gameObject> objects;
 public:
  Driver(int &argc = 0, char **argv = 0);
  ~Driver();
  bindObj(const gameObject &gs);
  startGame();
  endGame();

};
#endif
