#include "CDriver.h"
#include "GameInfo.h"
#include "../network/netclient.h"
#include "../network/stream.h"

namespace td {

CDriver* CDriver::instance_ = NULL;

CDriver::CDriver(MainWindow* mainWindow)
        : QObject(), human_(NULL), mainWindow_(mainWindow), contextMenu_(NULL),
        projectile_(NULL)
{
    mgr_ = new ResManager();
}

CDriver::~CDriver() {
    delete gameTimer_;
    delete mgr_;
}

CDriver* CDriver::init(MainWindow* mainWindow) {
    if (instance_ != NULL) {
        return instance_;
    }
    instance_ = new CDriver(mainWindow);
    return instance_;
}

void CDriver::shutdown() {
    delete instance_;
    instance_ = NULL;
}

void CDriver::connectToServer(const QString& servaddr) {
    NetworkClient::init(QHostAddress(servaddr));
}

void CDriver::disconnectFromServer() {
    NetworkClient::instance()->shutdown();
}

void CDriver::updateServer(GameObject* obj) {
    Stream* updates = new Stream();

    if (obj->getID() == 0xFFFFFFFF) {
        return;
    }

    obj->networkWrite(updates);

    NetworkClient::instance()->send(network::kPlayerPosition,
                                        updates->data());
    delete updates;
}

void CDriver::readObject(Stream* s) {
    unsigned int id = s->readInt();

    if (id == human_->getID()) {
        return;
    }

    GameObject* go = mgr_->findObject(id);
    if (go == NULL) {

        go = mgr_->createObjectWithID(id);

        if (((id & 0xFF000000) >> 24) == Player::clsIdx()) {
            qDebug("Creating new Player");
            GraphicsComponent* graphics = new PlayerGraphicsComponent();
            go->setGraphicsComponent(graphics);

            connect(gameTimer_, SIGNAL(timeout()), go, SLOT(update()));
        }
    }
    
    go->networkRead(s);
    delete s;
}

void CDriver::createHumanPlayer(MainWindow *gui) {
    
    Stream* request = new Stream();
    PhysicsComponent* physics = new PlayerPhysicsComponent();
    GraphicsComponent* graphics = new PlayerGraphicsComponent();
    PlayerInputComponent* input = new PlayerInputComponent();
    human_ = new Player();
    human_->setID(0xFFFFFFFF);
    human_->setInputComponent(input);
    human_->setGraphicsComponent(graphics);
    human_->setPhysicsComponent(physics);

    connect(gui, SIGNAL(signalKeyPressed(int)), input, SLOT(keyPressed(int)));
    connect(gui, SIGNAL(signalKeyReleased(int)), input, SLOT(keyReleased(int)));
    // Connection for collisions -- waiting on map object
    connect(physics, SIGNAL(requestTileInfo(int, int, int*)), 
            gameMap_, SLOT(getTileInfo(int, int, int*)));

    request->writeByte(Player::clsIdx());
    NetworkClient::instance()->send(network::kRequestPlayerID, request->data());
    delete request;
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

    Stream* request = new Stream();
    tower_ = new Tower();
    Tile* currentTile = gameMap_->getTile(pos.x(), pos.y());
    GraphicsComponent* graphics = new TowerGraphicsComponent();

    tower_->setPos(currentTile->getPos());
    tower_->setGraphicsComponent(graphics);
    tower_->setID(0xFFFFFFFF);
    connect(gameTimer_, SIGNAL(timeout()), tower_, SLOT(update()));
    
    request->writeByte(Tower::clsIdx());
    NetworkClient::instance()->send(network::kRequestTowerID, request->data());
    delete request;
}

void CDriver::startGame() {
    // Create hard coded map
    gameMap_     = new Map(16, 21);
    gameMap_->loadTestMap2();
    gameTimer_   = new QTimer(this);

    connectToServer("127.0.0.1");
    connect(NetworkClient::instance(), SIGNAL(UDPReceived(Stream*)),
            this, SLOT(UDPReceived(Stream*)));

    createHumanPlayer(mainWindow_);
    contextMenu_ = new ContextMenu(human_);
    createNPC();

    connect(contextMenu_, SIGNAL(signalPlayerMovement(bool)),
	    human_->getInputComponent(), SLOT(playerMovement(bool)));
    connect(mainWindow_,  SIGNAL(signalSpacebarPressed()),
            contextMenu_, SLOT(toggleMenu()));
    connect(mainWindow_,  SIGNAL(signalNumberPressed(int)),
            contextMenu_, SLOT(selectMenuItem(int)));
    connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
            contextMenu_, SLOT(viewResources(bool)));
    connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
            npc_->getGraphicsComponent(), SLOT(showHealth(bool)));
    connect(gameTimer_,   SIGNAL(timeout()), 
            human_,       SLOT(update()));
    /* TODO: alter temp solution */
    connect(contextMenu_, SIGNAL(signalTowerSelected(int, QPointF)),
            this,         SLOT(createTower(int, QPointF)));

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
        case network::kRequestPlayerID: /* Hack for Single Player */
            human_->setID(Player::clsIdx() << 24);
            mgr_->addExistingObject(human_);
            break;
        case network::kRequestTowerID:
	    tower_->setID(Tower::clsIdx());
            mgr_->addExistingObject(tower_);
            break;
        case network::kAssignPlayerID:
            //read ID and add human to existing objects
            if (human_->getID() == 0xFFFFFFFF) {
                human_->setID(s->readInt());
                mgr_->addExistingObject(human_);
                qDebug("Got an ID from the server!");
            }
            break;
        case network::kAssignTowerID:
            if(tower_->getID() == 0xFFFFFFFF) {
              tower_->setID(s->readInt());
              mgr_->addExistingObject(tower_);
            }
            break;
        default:
            this->readObject(s);
            break;
    }
}

} /* end namespace td */
