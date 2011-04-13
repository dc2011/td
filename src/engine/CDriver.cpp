#include "CDriver.h"
#include <map.h>
#include <tile.h>
#include "ContextMenu.h"
#include "GameObject.h"
#include "Map.h"
#include "NPC.h"
#include "Player.h"
#include "Projectile.h"
#include "ResManager.h"
#include "Tower.h"
#include "BuildingTower.h"
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
        mainWindow_(mainWindow), contextMenu_(NULL)
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

void CDriver::sendNetMessage(unsigned char msgType, QByteArray msg) {
    NetworkClient::instance()->send(msgType, msg);
}

void CDriver::setBaseHealth(int health) {
    Driver::setBaseHealth(health);

    /* Do something dramatic here */
    Console::instance()->addText("Oh teh noes!");
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

        /* I was so looking forward to avoiding this stuff... *sigh* */
        if (go->getClsIdx() == NPC::clsIdx()) {
            connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
                    go->getGraphicsComponent(), SLOT(showHealth(bool)));
        }

        if (go->getClsIdx() == BuildingTower::clsIdx()) {
            Tile* tile = gameMap_->getTile(((TileExtension*)go)->getPos());
            tile->setActionType(TILE_BUILDING);
            tile->setExtension((BuildingTower*)go);
        }

        if (go->getClsIdx() == Tower::clsIdx()) {
            Tile* tile = gameMap_->getTile(((TileExtension*)go)->getPos());
            tile->setActionType(TILE_BUILT);
            tile->setExtension((Tower*)go);
        }

        connect(gameTimer_, SIGNAL(timeout()), go, SLOT(update()));
        return;
    } else if (go == (GameObject*)-1) {
        go = mgr_->createTempObject((id & 0xFF000000) >> 24);
        go->networkRead(s);
        delete go;
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
    connect(physics, SIGNAL(NPCPlayerCollided(int)), 
            human_, SLOT(createEffect(int)));
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
            this,         SLOT(requestBuildingTower(int, QPointF)));
    connect(human_, SIGNAL(signalEmptyEffectList()),
            physics, SLOT(okayToPlayCollisionSfx()));
    
    // resource harvesting and dropping
    connect(this, SIGNAL(signalHarvesting(int)),
            player, SLOT(startHarvesting(int)));
    connect(mainWindow_, SIGNAL(signalSpacebarReleased()),
            player, SLOT(stopHarvesting()));
    connect(this, SIGNAL(signalEmptyTile(bool)),
            player, SLOT(dropResource(bool)));
    connect(player, SIGNAL(signalPlayerMovement(bool)),
	        input, SLOT(playerMovement(bool)));
    connect(player, SIGNAL(signalDropResource(int, QPointF, QVector2D)),
            this, SLOT(requestCollectable(int, QPointF, QVector2D)));
}

void CDriver::requestBuildingTower(int type, QPointF pos) {
    if (isSinglePlayer()) {
        BuildingTower* t = Driver::createBuildingTower(type, pos);
        human_->dropResource(Driver::addToTower(t, human_));
    } else {
        Stream s;
        s.writeInt(human_->getID());
        s.writeInt(type);
        s.writeFloat(pos.x());
        s.writeFloat(pos.y());
        NetworkClient::instance()->send(network::kTowerChoice, s.data());
    }
}

void CDriver::requestResourceAddition(BuildingTower* t) {
    if (isSinglePlayer()) {
        if (addToTower(t, human_)) {
            if (t->isDone()) {
                Driver::createTower(t->getType(), t->getPos());
                destroyObject(t);
            }
            human_->dropResource(true);
        } else {
            human_->dropResource(false);
        }
    } else {
        Stream s;
        s.writeInt(human_->getID());
        s.writeFloat(t->getPos().x());
        s.writeFloat(t->getPos().y());
        NetworkClient::instance()->send(network::kDropResource, s.data());
    }
}

void CDriver::requestSellTower(QPointF pos) {
    if (isSinglePlayer()) {
        Driver::sellTower(pos);
    } else {
        /*
        Stream s;
        s.writeInt(human_->getID());
        s.writeFloat(t->getPos().x());
        s.writeFloat(t->getPos().y());
        NetworkClient::instance()->send(network::kSellTower, s.data());
        */
    }
}
void CDriver::NPCCreator() {
    NPC* npc = NULL;

    if (npcCounter_++ % 15 == 0 && (npcCounter_ % 400) > 300) {
        npc = Driver::createNPC(NPC_FLY);
    }
    if (npcCounter_ % 40 == 0 && (npcCounter_ % 1400) > 1000) {
        npc = Driver::createNPC(NPC_SLOW);
    }

    if (npc) {
        if ((npcCounter_ % 2) == 0) {
            npc->setGem(1);
        } else {
            npc->setGem(0);
        }
        connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
                npc->getGraphicsComponent(), SLOT(showHealth(bool)));
        connect(gameTimer_, SIGNAL(timeout()), npc, SLOT(update()));
    }
}

void CDriver::startGame(bool singlePlayer) {
    // Create hard coded map
    gameMap_ = new Map(mainWindow_->getMD()->map(), this);
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

    gameTimer_->start(GAME_TICK_INTERVAL);
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
    BuildingTower* t = (BuildingTower*)currentTile->getExtension();

    switch (currentTile->getActionType()) {

        case TILE_BUILDABLE:
            contextMenu_->toggleMenu();
            break;

        case TILE_BUILDING:
            requestResourceAddition(t);
            break;
        case TILE_BUILT:
            //TODO Tower upgrade/sell context menu toggle
            requestSellTower(currentTile->getPos());
        case TILE_BASE:
            //TODO Player upgrade context menu toggle
            break;

        case TILE_RESOURCE:
            emit signalHarvesting(currentTile->getTiledTile()->id());
            break;

        default:
            emit signalEmptyTile(false);
    }
}

void CDriver::UDPReceived(Stream* s) {
    int message = s->readByte(); /* Message Type */

    switch(message) {
        case network::kAssignPlayerID:
        {
            playerID_ = s->readInt();
            break;
        }
        case network::kMulticastIP:
        {
            unsigned char mcast = s->readByte();
            NetworkClient::instance()->setMulticastAddress(mcast);
            break;
        }
        case network::kServerPlayers:
        {
            int count = s->readByte();
            for (int i = 0; i < count; i++) {
                unsigned int id = s->readInt();
                GameObject* go = mgr_->createObjectWithID(id);
                go->networkRead(s);
                go->initComponents();
                connect(gameTimer_, SIGNAL(timeout()), go, SLOT(update()));
                connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
                        (Player*)go,  SLOT(showName(bool)));

                if (id == playerID_) {
                    this->makeLocalPlayer((Player*)go);
                }
            }
            break;
        }
        case network::kServerUpdate:
        case network::kNPCWave:
        {
            int count = s->readShort();
            for (int i = 0; i < count; i++) {
                readObject(s);
            }
            break;
        }
        case network::kDropResource:
        {
            unsigned int id = s->readInt();
            bool addToTower = s->readInt();
            
            if (human_->getID() == id) {
                human_->dropResource(addToTower);
            }
            break;
        }
        case network::kDestroyObject:
        {  
            int id = s->readInt();
            destroyObject(id);
            break;
        }
        case network::kBaseHealth:
        {
            int health = s->readInt();

            setBaseHealth(health);
            break;
        }
        case network::kGameOver:
        {
            bool successful = s->readByte();

            if (successful) {
                Console::instance()->addText("You won :D");
            } else {
                Console::instance()->addText("You lost :(");
            }
            break;
        }
        case network::kConsoleChat:
        {
            int playerID = s->readInt();
            Player* p = (Player*)mgr_->findObject(playerID);

            if (p == NULL || p == (Player*)-1) {
                return;
            }

            int length = s->readInt();
            QString text = s->read(length);

            if (!text.isEmpty()) {
                QString line = "[" + p->getNickname() + "] " + text;
                Console::instance()->addText(line);
            }
            break;
        }
        case network::kVoiceMessage:
        {
            AudioManager::instance()->addToQueue(s);
            return;
        }
        case network::kPlaySfx:
        {
            int type = s->readInt();
            int len = s->readInt();
            QString fname = QString(s->read(len));

            AudioManager::instance()->playSfx(fname, (SoundType)type);
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
