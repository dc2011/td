#include "CDriver.h"
#include <map.h>
#include <tile.h>
#include "ContextMenu.h"
#include "GameInfo.h"
#include "GameObject.h"
#include "Map.h"
#include "NPC.h"
#include "Player.h"
#include "Projectile.h"
#include "ResManager.h"
#include "Tower.h"
#include "Unit.h"
#include "../client/MainWindow.h"
#include "../graphics/MapDisplayer.h"
#include "../graphics/PixmapFiles.h"
#include "../network/netclient.h"
#include "../network/stream.h"
#include "../util/defines.h"

namespace td {

CDriver* CDriver::instance_ = NULL;
QTimer* CDriver::gameTimer_;

CDriver::CDriver(MainWindow* mainWindow)
        : QObject(), playerID_(0xFFFFFFFF), human_(NULL), mainWindow_(mainWindow),
        contextMenu_(NULL), projectile_(NULL)
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

    if (id == playerID_) {
        s->read(s->size() - s->position());
        return;
    }

    GameObject* go = mgr_->findObject(id);
    if (go == NULL) {
        go = mgr_->createObjectWithID(id);
        go->networkRead(s);
        go->initComponents();
        connect(gameTimer_, SIGNAL(timeout()), go, SLOT(update()));

        return;
    }
    
    go->networkRead(s);
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

void CDriver::makeLocalPlayer(Player* player) {
    PhysicsComponent* physics = new PlayerPhysicsComponent();
    PlayerInputComponent* input = new PlayerInputComponent();

    player->setPhysicsComponent(physics);
    player->setInputComponent(input);
    human_ = player;

    /* Connect to arrow key events */
    connect(mainWindow_, SIGNAL(signalKeyPressed(int)),
            input, SLOT(keyPressed(int)));
    connect(mainWindow_, SIGNAL(signalKeyReleased(int)),
            input, SLOT(keyReleased(int)));

    // Connection for collisions -- waiting on map object
    connect(physics, SIGNAL(requestTileType(double, double, int*)), 
            gameMap_, SLOT(getTileType(double, double, int*)));

    // NPC -> Player effect
    connect(physics, SIGNAL(NPCPlayerCollided(Effect::EffectType)), 
            human_, SLOT(createEffect(Effect::EffectType)));
    connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
            player->getGraphicsComponent(), SLOT(showName(bool)));

    /* Set up the build context menu */
    contextMenu_ = new ContextMenu(human_);

    connect(contextMenu_, SIGNAL(signalPlayerMovement(bool)),
	        input,        SLOT(playerMovement(bool)));
    connect(mainWindow_,  SIGNAL(signalSpacebarPressed()),
            this,         SLOT(handleSpacebarPress()));
    connect(mainWindow_,  SIGNAL(signalNumberPressed(int)),
            contextMenu_, SLOT(selectMenuItem(int)));
    connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
            contextMenu_, SLOT(viewResources(bool)));
    /* TODO: alter temp solution */
    connect(contextMenu_, SIGNAL(signalTowerSelected(int, QPointF)),
            this,         SLOT(createTower(int, QPointF)));
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

void CDriver::createProjectile(QPointF source, QPointF target) {
    if (!tower_) {
        return;
    }
    PhysicsComponent* projectilePhysics = new ProjectilePhysicsComponent();
    GraphicsComponent* projectileGraphics = new ProjectileGraphicsComponent();
    ProjectileInputComponent* input = new ProjectileInputComponent();
    projectile_ = (Projectile*)mgr_->createObject(Projectile::clsIdx());

    input->setParent(projectile_);
    projectile_->setPhysicsComponent(projectilePhysics);
    projectile_->setGraphicsComponent(projectileGraphics);

    QPointF* start = new QPointF(source);
    QPointF* end = new QPointF(target);
    input->setPath(start, end);
    projectile_->setInputComponent(input);

    connect(gameTimer_,  SIGNAL(timeout()), projectile_, SLOT(update()));
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
    connect(tower_->getPhysicsComponent(), 
            SIGNAL(fireProjectile(QPointF, QPointF)),
            this, SLOT(createProjectile(QPointF, QPointF)));
    if(isSinglePlayer() == true) {
        mgr_->createObject(Tower::clsIdx());
    } else {
        request->writeByte(Tower::clsIdx());
        NetworkClient::instance()->send(network::kRequestTowerID, 
                                        request->data());
    }
    delete request;
}

void CDriver::startGame(bool singlePlayer) {
    // Create hard coded map
    CDriver::gameMap_     = new Map(mainWindow_->getMD()->map());
    CDriver::gameTimer_   = new QTimer(this);
    CDriver::gameMap_->initMap();
    QQueue<QString> musicList;

    /*if(singlePlayer == false) {
        connect(NetworkClient::instance(), SIGNAL(UDPReceived(Stream*)),
                this, SLOT(UDPReceived(Stream*)));
        connect(NetworkClient::instance(), SIGNAL(TCPReceived(Stream*)),
                this, SLOT(UDPReceived(Stream*)));
    }*/
    setSinglePlayer(singlePlayer);

    musicList = td::AudioManager::instance()->musicDir("./sound/music/");
    td::AudioManager::instance()->playMusic(musicList);

    if (singlePlayer) {
        Player* player = (Player*)mgr_->createObject(Player::clsIdx());
        playerID_ = player->getID();

        player->initComponents();
        connect(gameTimer_, SIGNAL(timeout()), player, SLOT(update()));

        this->makeLocalPlayer(player);
    }

    connect(gameTimer_, SIGNAL(timeout()), this, SLOT(NPCCreator()));
    //connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
            //npc_->getGraphicsComponent(), SLOT(showHealth(bool)));

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
	        contextMenu_->toggleMenu();
        case TILE_BASE:
            break;

        case TILE_RESOURCE:
            qDebug("Harvesting resource: %d", currentTile->getTiledTile()->id());
            break;
    }
}

QTimer* CDriver::getTimer() {
    return gameTimer_;
}

void CDriver::UDPReceived(Stream* s) {
    int message = s->readByte(); /* Message Type */

    switch(message) {
        case network::kRequestTowerID:
	        tower_->setID(Tower::clsIdx());
	        tower_->initComponents();
            mgr_->addExistingObject(tower_);
            break;
        case network::kAssignPlayerID:
            playerID_ = s->readInt();
            qDebug("My player ID is %08X", playerID_);
            break;
        case network::kServerPlayers:
        {
            int count = s->readByte();
            for (int i = 0; i < count; i++) {
                unsigned int id = s->readInt();
                GameObject* go = mgr_->createObjectWithID(id);
                go->networkRead(s);
                go->initComponents();
                connect(gameTimer_, SIGNAL(timeout()), go, SLOT(update()));

                if (id == playerID_) {
                    this->makeLocalPlayer((Player*)go);
                }
            }
            break;
        }
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

    if (!s->eof()) {
        this->UDPReceived(s);
    } else {
        delete s;
    }
}

} /* end namespace td */
