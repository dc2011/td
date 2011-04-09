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
#include "../audio/SfxManager.h"
#include "../client/MainWindow.h"
#include "../graphics/MapDisplayer.h"
#include "../graphics/PixmapFiles.h"
#include "../graphics/Console.h"
#include "../network/netclient.h"
#include "../network/stream.h"
#include "../util/defines.h"

namespace td {

CDriver* CDriver::instance_ = NULL;

CDriver::CDriver(MainWindow* mainWindow)
        : Driver(), playerID_(0xFFFFFFFF), human_(NULL),
        mainWindow_(mainWindow), contextMenu_(NULL), projectile_(NULL)
{
    mgr_ = new ResManager(this);
    npcCounter_ = 0;
}

CDriver::~CDriver() {
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

void CDriver::updateRT(GameObject* obj) {
    if (obj->getClsIdx() != Player::clsIdx() || isSinglePlayer()) {
        /* Only send updates for players, and only if there's a server */
        return;
    }

    Stream s;
    obj->networkWrite(&s);

    NetworkClient::instance()->send(network::kPlayerPosition, s.data());
}

void CDriver::readObject(Stream* s) {
    unsigned int id = s->readInt();

    if (id == playerID_) {
        Player p(this);
        p.networkRead(s);
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
    connect(physics, SIGNAL(NPCPlayerCollided(Effect*)), 
            human_, SLOT(createEffect(Effect*)));
    connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
            player, SLOT(showName(bool)));


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
    connect(human_, SIGNAL(signalEmptyEffectList()),
            physics, SLOT(okayToPlayCollisionSfx()));
}

void CDriver::NPCCreator() {
    if (npcCounter_++ % 15 == 0 && (npcCounter_ % 400) > 300) {
        createNPC(NPC_FLY);
    }
    if (npcCounter_ % 40 == 0 && (npcCounter_ % 1400) > 1000) {
        createNPC(NPC_SLOW);
    }
}

NPC* CDriver::createNPC(int npcType) {
    NPC* npc = (NPC*)mgr_->createObject(NPC::clsIdx());
    npc->setType(npcType);

    npc->initComponents();
    // connect(input, SIGNAL(deleteUnitLater(Unit*)),
    //this, SLOT(NPCDeleter(Unit*)), Qt::QueuedConnection);
    connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
            npc->getGraphicsComponent(), SLOT(showHealth(bool)));
    connect(gameTimer_, SIGNAL(timeout()), npc, SLOT(update()));
    return npc;
}

void CDriver::createProjectile(QPointF source, QPointF target, Unit* enemy) {
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
    projectile_->setEnemy(enemy);

    connect(gameTimer_,  SIGNAL(timeout()), projectile_, SLOT(update()));
}

void CDriver::createTower(int towerType, QPointF pos)
{
    if (isSinglePlayer()) {
        Tower* tower = (Tower*)mgr_->createObject(Tower::clsIdx());
        Tile* currentTile = gameMap_->getTile(pos.x(), pos.y());
        tower->setType(towerType);
        tower->initComponents();
        tower->setPos(currentTile->getPos());
        currentTile->setExtension(tower);

        connect(gameTimer_, SIGNAL(timeout()), tower, SLOT(update()));
        connect(tower->getPhysicsComponent(),
                SIGNAL(fireProjectile(QPointF, QPointF, Unit*)),
                this, SLOT(createProjectile(QPointF, QPointF, Unit*)));

        return;
    }

    Stream* s = new Stream();
    s->writeInt(human_->getID());
    s->writeInt(towerType);
    s->writeFloat(pos.x());
    s->writeFloat(pos.y());
    NetworkClient::instance()->send(network::kBuildTower, s->data());
    delete s;
}

void CDriver::startGame(bool singlePlayer) {
    // Create hard coded map
    gameMap_ = new Map(mainWindow_->getMD()->map());
    gameTimer_ = new QTimer(this);
    gameMap_->initMap();
    QQueue<QString> musicList;

    setSinglePlayer(singlePlayer);

    td::Console::instance();
    musicList = td::AudioManager::instance()->musicDir("./sound/music/");
    td::AudioManager::instance()->playMusic(musicList);

    if (singlePlayer) {
        Player* player = (Player*)mgr_->createObject(Player::clsIdx());
        playerID_ = player->getID();

        player->initComponents();
        connect(gameTimer_, SIGNAL(timeout()), player, SLOT(update()));

        this->makeLocalPlayer(player);

        connect(gameTimer_, SIGNAL(timeout()), this, SLOT(NPCCreator()));
    }

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
            break;

        case TILE_BUILT:
        case TILE_BASE:
            break;

        case TILE_RESOURCE:
            // TODO: remove SFX and do it properly
            PLAY_LOCAL_SFX(SfxManager::resourceLumber);
            qDebug("Harvesting resource: %d", currentTile->getTiledTile()->id());
            break;
    }
}

void CDriver::UDPReceived(Stream* s) {
    int message = s->readByte(); /* Message Type */

    switch(message) {
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
        case network::kServerUpdate:
        {
            int count = s->readShort();
            for (int i = 0; i < count; i++) {
                readObject(s);
            }
            break;
        }
        case network::kDestroyObject:
        {  
	        int id = s->readInt();
	        destroyObject(id);
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
