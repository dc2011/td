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
#include "../graphics/TowerGraphicsComponent.h"
#include "../network/netclient.h"
#include "../network/stream.h"

namespace td {

CDriver::CDriver(MainWindow *mainWindow)
        : QObject(), human_(NULL), mainWindow_(mainWindow), contextMenu_(NULL),
        projectile_(NULL)
{
    mgr_ = new ResManager();
}

CDriver::~CDriver() {
    AudioManager::instance()->shutdown();

    delete this->gameTimer_;
    delete mgr_;
}

void CDriver::connectToServer(const QString& servaddr) {
    NetworkClient::init(QHostAddress(servaddr));
}

void CDriver::disconnectFromServer() {
    NetworkClient::instance()->shutdown();
}

void CDriver::updateServer(GameObject* obj) {
    Stream* updates = new Stream();

    obj->networkWrite(updates);

    NetworkClient::instance()->send(network::kPlayerPosition,
                                        updates->data());
    delete updates;
}

void CDriver::readObject(Stream* s) {
    unsigned int id = s->readInt();

    GameObject* go = mgr_->findObject(id);
    if (go == NULL) {
        go = mgr_->createObject((id & 0xFF000000) >> 24);
    }
    
    go->networkRead(s);
    delete s;
}

void CDriver::createHumanPlayer(MainWindow *gui) {
    human_ = (Player*)mgr_->createObject(Player::clsIdx());

    PhysicsComponent* physics = new PlayerPhysicsComponent();
    GraphicsComponent* graphics = new PlayerGraphicsComponent();
    PlayerInputComponent* input = new PlayerInputComponent();
    human_->setInputComponent(input);
    human_->setGraphicsComponent(graphics);
    human_->setPhysicsComponent(physics);

    connect(gui, SIGNAL(signalKeyPressed(int)), input, SLOT(keyPressed(int)));
    connect(gui, SIGNAL(signalKeyReleased(int)), input, SLOT(keyReleased(int)));
    // Connection for collisions -- waiting on map object
    connect(physics, SIGNAL(requestTileInfo(int, int, int*)), 
            gameMap_, SLOT(getTileInfo(int, int, int*)));
}

void CDriver::createNPC() {
    npc_ = (NPC*)mgr_->createObject(NPC::clsIdx());

    PhysicsComponent* physics = new NPCPhysicsComponent();
    GraphicsComponent* graphics = new NPCGraphicsComponent();
    NPCInputComponent* input = new NPCInputComponent();

    input->setParent(npc_);
    npc_->setInputComponent(input);
    npc_->setPhysicsComponent(physics);
    npc_->setGraphicsComponent(graphics);

    connect(gameTimer_, SIGNAL(timeout()), npc_, SLOT(update()));
}

  void CDriver::createProjectile(){
      if (!tower_) {
          return;
      }
      //qDebug("fire projectile");
      PhysicsComponent* projectilePhysics = new ProjectilePhysicsComponent();
      GraphicsComponent* projectileGraphics = new ProjectileGraphicsComponent();
      ProjectileInputComponent* input = new ProjectileInputComponent();
      projectile_ = (Projectile*)mgr_->createObject(Projectile::clsIdx());

      input->setParent(projectile_);
      projectile_->setPhysicsComponent(projectilePhysics);
      projectile_->setGraphicsComponent(projectileGraphics);

      QPointF* start = new QPointF(tower_->getPos());
      QPointF* end = new QPointF(human_->getPos());
      input->setPath(start, end);
      projectile_->setInputComponent(input);

      connect(gameTimer_,   SIGNAL(timeout()),
                projectile_,       SLOT(update()));
  }

void CDriver::createTower(int towerType, QPointF pos) {
    tower_ = new Tower();
    Tile* currentTile = gameMap_->getTile(pos.x(), pos.y());
    tower_->setPos(currentTile->getPos());
    GraphicsComponent* graphics = new TowerGraphicsComponent();
    //PhysicsComponent*  physics  = new TowerPhysicsComponent();
    tower_->setGraphicsComponent(graphics);
    //tower->setPhysicsComponent(physics);
    connect(gameTimer_, SIGNAL(timeout()), tower_, SLOT(update()));
}

void CDriver::startGame() {
    // Create hard coded map
    CDriver::gameMap_     = new Map(16, 21);
    CDriver::gameMap_->loadTestMap2();
    CDriver::gameTimer_   = new QTimer(this);


    createHumanPlayer(mainWindow_);
    contextMenu_ = new ContextMenu(human_);
    createNPC();

    connect(contextMenu_, SIGNAL(signalPlayerMovement(bool)),
	    human_->getInputComponent(), SLOT(playerMovement(bool)));
    connect(mainWindow_,  SIGNAL(signalSpacebarPressed()),
            contextMenu_, SLOT(toggleMenu()));
    connect(mainWindow_,  SIGNAL(signalNumberPressed(int)),
            contextMenu_, SLOT(selectMenuItem(int)));
    connect(gameTimer_,   SIGNAL(timeout()), 
            human_,       SLOT(update()));
    /* TODO: alter temp solution */
    connect(contextMenu_, SIGNAL(signalTowerSelected(int, QPointF)),
            this,         SLOT(createTower(int, QPointF)));

    /* TODO: Remove this */
    QObject::connect(mainWindow_, SIGNAL(signalFPressed()),
            this, SLOT(createProjectile()));

    connectToServer("127.0.0.1");
    connect(NetworkClient::instance(), SIGNAL(UDPReceived(Stream*)),
            this, SLOT(UDPReceived(Stream*)));

    gameTimer_->start(30);
}

void CDriver::endGame() {
    disconnectFromServer();

    this->gameTimer_->stop();
}

void CDriver::UDPReceived(Stream* s) {
    s->readByte(); /* Message Type */

    this->readObject(s);
}

} /* end namespace td */
