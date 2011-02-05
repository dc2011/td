#ifndef DRIVER_H
#define DRIVER_H
#include <QtGui> 
#include <QWidget>
#include <QTimer>
#include <QApplication>
#include <QVector>
//#include "gameinfo.h"
#include "GameObject.h"
class Driver : public QApplication {
  
 private:
  GameInfo gameInfo;
  QTimer gameTimer;
  QVector<GameObject> objects;
 public:
  //ctors and dtors
  virtual Driver(int argc = 0, char **argv = 0);
  virtual ~Driver();
  //bind object slots to timer signals
  void bindAll();
  void bindSingle(const GameObject& obj);
  //start and stop game timers
  void startGame();
  void endGame();
  //load map from file, parse data, store in game info map property
  int loadMap(GameInfo &gi, char* map);
};
#endif
