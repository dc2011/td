#include "CDriver.h"
#include "GameInfo.h"
#include "../graphics/PixmapFiles.h"
#include "../network/netclient.h"
#include "../network/stream.h"
#include "ContextMenu.h"
#include "GameObject.h"
#include "Map.h"
#include "NPC.h"
#include "Player.h"
#include "Projectile.h"
#include "ResManager.h"
#include "Tower.h"
#include "Unit.h"
#include <map.h>
#include <tile.h>
#include "../client/MainWindow.h"
#include "../graphics/MapDisplayer.h"
#include "../util/defines.h"

namespace td {

CDriver* CDriver::instance_ = NULL;
QTimer* CDriver::gameTimer_;

CDriver::CDriver(MainWindow* mainWindow)
        : QObject(), human_(NULL), mainWindow_(mainWindow), contextMenu_(NULL),
        projectile_(NULL)
{
    mgr_ = new ResManager();
    npc_ = QSet<NPC*>();
    npcCounter_ = 0;
    tower_ = NULL;
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
    if(CDriver::instance()->isSinglePlayer() == true) {
	delete updates;
	return;
    }
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

        } else {
            go->initComponents();
        }
        connect(gameTimer_, SIGNAL(timeout()), go, SLOT(update()));
    }
    
    go->networkRead(s);
    delete s;
}

void CDriver::destroyObjSync(int id) {
    Stream* out = new Stream();
    if(mgr_->findObject(id) == NULL) {
	return;
    }
    mgr_->deleteObject(id);
    out->writeInt(id);
    NetworkClient::instance()->send(network::kClientDestroyObj, out->data());
}

void CDriver::destroyObjLocal(int id) {
    if(mgr_->findObject(id) == NULL) {
	return;
    }
    mgr_->deleteObject(id);
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
    connect(physics, SIGNAL(requestTileType(double, double, int*)), 
            gameMap_, SLOT(getTileType(double, double, int*)));
    // NPC -> Player effect
    QObject::connect(physics, SIGNAL(NPCPlayerCollided(Effect::EffectType)), human_, SLOT(createEffect(Effect::EffectType)));
    if(isSinglePlayer() == true) {
	mgr_->createObject(Player::clsIdx());
    } else {
	request->writeByte(Player::clsIdx());
	NetworkClient::instance()->send(network::kRequestPlayerID, request->data());
    }
    delete request;
}

void CDriver::NPCCreator() {
    if (npcCounter_++ % 15 == 0 && (npcCounter_ % 400) > 300) {
        npc_.insert(createNPC());
    }
}

void CDriver::NPCDeleter(Unit* npc) {
    npc_.remove((NPC*)npc);
    mgr_->deleteObject(npc);
}

NPC* CDriver::createNPC() {
    NPC* npc = (NPC*)mgr_->createObject(NPC::clsIdx());

    npc->initComponents();
    // connect(input, SIGNAL(deleteUnitLater(Unit*)),
    //this, SLOT(NPCDeleter(Unit*)), Qt::QueuedConnection);
    connect(gameTimer_, SIGNAL(timeout()), npc, SLOT(update()));
    return npc;
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

    tower_->initComponents(towerType);
    tower_->setPos(currentTile->getPos());
    tower_->setID(0xFFFFFFFF);
    currentTile->setExtension(tower_);

    connect(gameTimer_, SIGNAL(timeout()), tower_, SLOT(update()));
    if(isSinglePlayer() == true) {
	mgr_->createObject(Tower::clsIdx());
    } else {
	request->writeByte(Tower::clsIdx());
	NetworkClient::instance()->send(network::kRequestTowerID, request->data());
    }
    delete request;
}

void CDriver::startGame(bool singlePlayer) {
    // Create hard coded map
    CDriver::gameMap_     = new Map(mainWindow_->getMD()->map());
    CDriver::gameTimer_   = new QTimer(this);
    CDriver::gameMap_->initMap();
    QQueue<QString> musicList;

    if(singlePlayer == false) {
	connect(NetworkClient::instance(), SIGNAL(UDPReceived(Stream*)),
		this, SLOT(UDPReceived(Stream*)));
    }
    setSinglePlayer(singlePlayer);

    musicList = td::AudioManager::instance()->musicDir("./sound/music/");
    td::AudioManager::instance()->playMusic(musicList);

    createHumanPlayer(mainWindow_);
    contextMenu_ = new ContextMenu(human_);

    connect(contextMenu_, SIGNAL(signalPlayerMovement(bool)),
	    human_->getInputComponent(), SLOT(playerMovement(bool)));
    connect(mainWindow_,  SIGNAL(signalSpacebarPressed()),
            this,         SLOT(handleSpacebarPress()));
    connect(mainWindow_,  SIGNAL(signalNumberPressed(int)),
            contextMenu_, SLOT(selectMenuItem(int)));
    connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
            contextMenu_, SLOT(viewResources(bool)));
    //connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
            //npc_->getGraphicsComponent(), SLOT(showHealth(bool)));
    connect(gameTimer_,   SIGNAL(timeout()), 
            human_,       SLOT(update()));
    connect(gameTimer_, SIGNAL(timeout()), this, SLOT(NPCCreator()));

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

bool CDriver::isSinglePlayer() {
    return singlePlayer_;
}
void CDriver::setSinglePlayer(bool singlePlayer) {
    singlePlayer_ = singlePlayer;
}
void CDriver::handleSpacebarPress() {
    Tile* currentTile = gameMap_->getTile(human_->getPos());

    switch (currentTile->getActionType()) {

        case TILE_BUILDABLE:
            contextMenu_->toggleMenu();
            currentTile->setActionType(TILE_BUILT); 
            break;

        case TILE_BUILT:
        case TILE_BASE:
            break;

        case TILE_RESOURCE:
            qDebug("Harvesting resource: %d", currentTile->getTiledTile()->id());
            break;
    }
}

void CDriver::deadNPC(int id) {
    if(singlePlayer_ == true) {
        destroyObjLocal(id);
    } else {
        destroyObjSync(id);
    }
}

QTimer* CDriver::getTimer() {
    return gameTimer_;
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
	    tower_->initComponents();
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
	      tower_->initComponents();
              mgr_->addExistingObject(tower_);
            }
            break;
        case network::kServerDestroyObj:
	{
	    int id = s->readInt();
	    destroyObjLocal(id);
	    break;
	}
        default:
            this->readObject(s);
            break;
    }
}

} /* end namespace td */
