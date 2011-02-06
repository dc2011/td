#ifndef CDRIVER_H
#define CDRIVER_H
#include <QTimer>
#include <QApplication>
#include <QVector>
#include "Player.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerInputComponent.h"
//#include "GameInfo.h"
//#include "GameObject.h"
class CDriver : public QObject {
  
 private:
  //  GameInfo gameInfo;
  QTimer* gameTimer_;
  Player* human_;
  //QVector<GameObject> objects;
 public:
  //ctors and dtors
  CDriver(QObject *parent = 0);
  ~CDriver();
  Player* createHumanPlayer();
  //bind object slots to timer signals
  void bindAll();
  void bindSingle(const GameObject& obj);
  //start and stop game timers
  void startGame();
  void endGame();
  //load map from file, parse data, store in game info map property
  //int loadMap(GameInfo &gi, char* map);
};
#endif
