#include <QtGui>
#include <QTimer>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QWidget>
#include "GameInfo.h"
#include "GameObject.h"
#include "CDriver.h"
#include "../network/netclient.h"

namespace td {
  CDriver::CDriver(MainWindow *mainWindow) {
      mainWindow_ = mainWindow;
  }

  CDriver::~CDriver() {
    delete CDriver::gameTimer_;
    delete CDriver::human_;
  }


  //void CDriver::bindAll() {
  // QVector<GameObject>::iterator it;
  //for(it = CDriver::objects.begin(); it != CDriver::objects.end(); ++it) {
  // bindSingle(*it);
  //}
  //}

  void CDriver::bindSingle(const GameObject& obj) {
    //  connect(&CDriver::gameTimer_, SIGNAL(timeout()), obj, SLOT(update()));
  }
  void CDriver::connectToServer(char * servaddr) {
    td::NetworkClient::init(QHostAddress(servaddr));
  }
  void CDriver::disconnectFromServer() {
    td::NetworkClient::instance() -> shutdown();
  }
  Player* CDriver::createHumanPlayer(MainWindow *gui) {
    PhysicsComponent* physics = new PlayerPhysicsComponent();
    GraphicsComponent* graphics = new PlayerGraphicsComponent("arrow.png");

    InputComponent* input = new PlayerInputComponent();
    gui->installEventFilter(input);
    
    return new Player(input, physics, graphics);
  }

  void CDriver::startGame() {
    CDriver::gameTimer_ -> start(30);
  }

  void CDriver::endGame() {
    CDriver::gameTimer_ -> stop();
    //cleanup code
  }

  //int CDriver::loadMap(char* map) {
  //open map file, parse all map data, create map object,
  //create tiles and stuff, store everything in map object, store map object
  //in gameinfo.

  //return false on any type of failure,
  //return true on success
  //}
}
