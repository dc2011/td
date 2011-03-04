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
#include "Unit.h"
#include "../graphics/ProjectileGraphicsComponent.h"
#include "../network/netclient.h"
#include "../network/stream.h"

namespace td {

  CDriver::CDriver(MainWindow *mainWindow)
      : QObject(), human_(NULL), contextMenu_(NULL), projectile_(NULL) {
      mainWindow_ = mainWindow;
  }

  CDriver::~CDriver() {
    delete this->gameTimer_;
    delete this->human_;
    delete this->projectile_;
    td::AudioManager::instance()->shutdown();
  }

  void CDriver::connectToServer(char * servaddr) {
    td::NetworkClient::init(QHostAddress(servaddr));
  }
  void CDriver::disconnectFromServer() {
    td::NetworkClient::instance()->shutdown();
  }
  void CDriver::updateServer(Unit* u)
  {
    td::Stream* updates = new Stream();
    u->networkWrite(updates);
    td::NetworkClient::instance()->send(td::network::kPlayerPosition,
                                        updates->data());
    delete updates;
  }

  void CDriver::updatePlayer(Unit* u)
  {
    td::Stream* updates = new Stream();
    u->networkRead(updates);
    delete updates;
  }
  Player* CDriver::createHumanPlayer(MainWindow *gui) {
    PhysicsComponent* physics = new PlayerPhysicsComponent();
    GraphicsComponent* graphics = new PlayerGraphicsComponent();
    PlayerInputComponent* input = new PlayerInputComponent();
    CollisionComponent* collision = new CollisionComponent();
    //gui->installEventFilter(input);
    connect(gui, SIGNAL(signalKeyPressed(int)), input, SLOT(keyPressed(int)));
    connect(gui, SIGNAL(signalKeyReleased(int)), input, SLOT(keyReleased(int)));
    // Connection for collisions -- waiting on map object
    /*
    connect(collision, SIGNAL(requestTileInfo(int, int, int*)), map,
            SLOT(getTileInfo(int, int, int*)));
    */
    return new Player((InputComponent*) input, physics, graphics, collision);
  }

  void CDriver::createProjectile(){
      //qDebug("fire projectile");
      PhysicsComponent* projectilePhysics = new ProjectilePhysicsComponent();
      GraphicsComponent* projectileGraphics = new ProjectileGraphicsComponent();
      QPointF* start = new QPointF(human_->getPos());
      QPointF* end = new QPointF(100, 100);
      CDriver::projectile_ = new Projectile(projectilePhysics, projectileGraphics,
                                         start, end);
      connect(gameTimer_,   SIGNAL(timeout()),
                projectile_,       SLOT(update()));
  }

    void CDriver::startGame() {
        // Create hard coded map
        CDriver::gameMap_     = new Map(16, 21);
        CDriver::gameMap_->loadTestMap2();
        CDriver::gameTimer_   = new QTimer(this);
        CDriver::human_       = createHumanPlayer(mainWindow_);
        CDriver::contextMenu_ = new ContextMenu(human_);

        connect(mainWindow_,  SIGNAL(signalSpacebarPressed()),
                contextMenu_, SLOT(toggleMenu()));
        connect(mainWindow_,  SIGNAL(signalNumberPressed(int)),
                contextMenu_, SLOT(selectMenuItem(int)));
        connect(gameTimer_,   SIGNAL(timeout()), 
                human_,       SLOT(update()));
        QObject::connect(mainWindow_, SIGNAL(signalFPressed()), this, SLOT(createProjectile()));

        CDriver::gameTimer_->start(30);
    }

  void CDriver::endGame() {
    this->gameTimer_->stop();
  }
}
