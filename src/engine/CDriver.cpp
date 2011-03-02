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
        : QObject(), human_(NULL), mainWindow_(mainWindow), contextMenu_(NULL),
        projectile_(NULL)
{
    mgr_ = new ResManager();
}

CDriver::~CDriver() {
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
    
    Stream* request = new Stream();
    PhysicsComponent* physics = new PlayerPhysicsComponent();
    GraphicsComponent* graphics = new PlayerGraphicsComponent();
    PlayerInputComponent* input = new PlayerInputComponent();

    human_ = new Player(input, physics, graphics);

    connect(gui, SIGNAL(signalKeyPressed(int)), input, SLOT(keyPressed(int)));
    connect(gui, SIGNAL(signalKeyReleased(int)), input, SLOT(keyReleased(int)));

    request->writeByte(Player::clsIdx());

    NetworkClient::instance()->send(network::kRequestObjID, request->data());
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
    gameTimer_   = new QTimer(this);

    connectToServer("127.0.0.1");
    connect(NetworkClient::instance(), SIGNAL(UDPReceived(Stream*)),
            this, SLOT(UDPReceived(Stream*)));

    createHumanPlayer(mainWindow_);
    contextMenu_ = new ContextMenu(human_);

    connect(mainWindow_,  SIGNAL(signalSpacebarPressed()),
            contextMenu_, SLOT(toggleMenu()));
    connect(mainWindow_,  SIGNAL(signalNumberPressed(int)),
            contextMenu_, SLOT(selectMenuItem(int)));
    connect(gameTimer_,   SIGNAL(timeout()), 
            human_,       SLOT(update()));

    /* TODO: Remove this */
    QObject::connect(mainWindow_, SIGNAL(signalFPressed()),
            this, SLOT(createProjectile()));

    gameTimer_->start(30);
}

void CDriver::endGame() {
    disconnectFromServer();

    this->gameTimer_->stop();
}

void CDriver::UDPReceived(Stream* s) {
    int message = s->readByte(); /* Message Type */

    switch(message) {

        case network::kAssignObjID:

            //read ID and add human to existing objects
            human_->setID(s->readInt());
            mgr_->addExistingObject(human_);
            break;

        default:

            //TEMPORARY
            this->readObject(s);
            break;

    }    

}

} /* end namespace td */
