#include "CDriver.h"
#include <map.h>
#include <tile.h>
#include "ContextMenuTypes.h"
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
#include "Parser.h"

namespace td {

CDriver* CDriver::instance_ = NULL;

CDriver::CDriver(MainWindow* mainWindow)
        : Driver(), playerID_(0xFFFFFFFF), human_(NULL),
        mainWindow_(mainWindow), buildContextMenu_(NULL)
{
    mgr_ = new ResManager(this);
    npcCounter_ = 0;
}

CDriver::~CDriver() {
    if(!waves_.empty()) {
        NPCWave* temp;
        foreach(temp, waves_){
            disconnect(temp, SIGNAL(waveDead()),this,SLOT(deadWave()));
        }
    }
    waves_.clear();
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
    getMainWindow()->getStats()->updateHP(health);
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
    connect(physics, SIGNAL(pickupCollectable(double, double, Unit*)), human_, SLOT(pickupCollectable(double,double,Unit*)));
    /* Connect to arrow key events */
    connect(mainWindow_, SIGNAL(signalKeyPressed(int)),
            input, SLOT(keyPressed(int)));
    connect(mainWindow_, SIGNAL(signalKeyReleased(int)),
            input, SLOT(keyReleased(int)));

    /* Connect movement to window scrolling. */
    connect(player, SIGNAL(signalPlayerMovement(QPointF)),
            mainWindow_, SLOT(scroll(QPointF)));

    // Connection for collisions -- waiting on map object
    connect(physics, SIGNAL(requestTileType(double, double, int*)), 
            gameMap_, SLOT(getTileType(double, double, int*)));

    // NPC -> Player effect
    connect(physics, SIGNAL(NPCPlayerCollided(int)), 
            human_, SLOT(createEffect(int)));
    connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
            player, SLOT(showName(bool)));

    // set up the build context menu
    buildContextMenu_ = new BuildContextMenu(human_);
    connect(mainWindow_, SIGNAL(signalNumberPressed(int)),
            buildContextMenu_, SLOT(selectMenuItem(int)));
    connect(mainWindow_, SIGNAL(signalAltHeld(bool)),
            buildContextMenu_, SLOT(viewResources(bool)));
    connect(buildContextMenu_, SIGNAL(signalTowerSelected(int, QPointF)),
            this, SLOT(requestBuildingTower(int, QPointF)));
    connect(buildContextMenu_, SIGNAL(signalPlayerMovement(bool)),
	        input, SLOT(playerMovement(bool)));

    // set up the tower context menu
    towerContextMenu_ = new TowerContextMenu(human_);
    connect(mainWindow_, SIGNAL(signalNumberPressed(int)),
            towerContextMenu_, SLOT(selectMenuItem(int)));
    connect(mainWindow_, SIGNAL(signalAltHeld(bool)),
            towerContextMenu_, SLOT(viewResources(bool)));
    connect(towerContextMenu_, SIGNAL(signalSellTower(QPointF)),
            this, SLOT(requestSellTower(QPointF)));
    connect(towerContextMenu_, SIGNAL(signalUpgradeTower(QPointF)),
            this, SLOT(requestUpgradeTower(QPointF)));
    connect(towerContextMenu_, SIGNAL(signalPlayerMovement(bool)),
	        input, SLOT(playerMovement(bool)));
    
    // set up the player context menu
    playerContextMenu_ = new PlayerContextMenu(human_);
    connect(mainWindow_, SIGNAL(signalNumberPressed(int)),
            playerContextMenu_, SLOT(selectMenuItem(int)));
    connect(mainWindow_, SIGNAL(signalAltHeld(bool)),
            playerContextMenu_, SLOT(viewResources(bool)));
    //connect(playerContextMenu_, SIGNAL(signalUpgradePlayer(int, QPointF)),
    //TODO macca add upgrade player here        this, SLOT(***(int, QPointF)));
    connect(playerContextMenu_, SIGNAL(signalPlayerMovement(bool)),
	        input, SLOT(playerMovement(bool)));

    connect(mainWindow_, SIGNAL(signalSpacebarPressed()),
            this, SLOT(handleSpacebarPress()));
    connect(human_, SIGNAL(signalEmptyEffectList()),
            physics, SLOT(okayToPlayCollisionSfx()));
    
    // resource harvesting and dropping
    
    connect(this, SIGNAL(signalDropResource()),
            this, SLOT(dropResource()));
    connect(human_, SIGNAL(signalPickupCollectable(int)),
            this, SLOT(pickupCollectable(int)));

    connect(this, SIGNAL(signalHarvesting(int)),
            player, SLOT(startHarvesting(int)));
    connect(mainWindow_, SIGNAL(signalSpacebarReleased()),
            player, SLOT(stopHarvesting()));
    connect(player, SIGNAL(signalPlayerMovement(bool)),
	        input, SLOT(playerMovement(bool)));
    connect(player, SIGNAL(signalDropResource(int, QPointF, QVector2D)),
            this, SLOT(requestCollectable(int, QPointF, QVector2D)));
}

void CDriver::dropResource() {
    Tile* currentTile = gameMap_->getTile(human_->getPos());

    if (this->isSinglePlayer() &&
            currentTile->getActionType() == TILE_BUILDING) {
        BuildingTower* t = (BuildingTower*)currentTile->getExtension();
        if (this->addToTower(t, human_) && t->isDone()) {
            this->createTower(t->getType(), t->getPos());
            this->destroyObject(t);
            human_->setResource(RESOURCE_NONE);
            return;
        }
    }

    if (this->isSinglePlayer()) {
        this->createCollectable(human_->getResource(), human_->getPos(),
                                this->getRandomVector());

        human_->setResource(RESOURCE_NONE);
    } else {
        Stream s;
        s.writeInt(human_->getID());
        s.writeInt(human_->getResource());

        NetworkClient::instance()->send(network::kDropCollect, s.data());
    }
}

void CDriver::pickupCollectable(int id) {
    if (!this->isSinglePlayer()) {
        Stream s;
        s.writeInt(human_->getID());
        s.writeInt(id);
        
        NetworkClient::instance()->send(network::kPickCollect, s.data());
    }
}

void CDriver::requestCollectable(int collType, QPointF source,
        QVector2D vel) {
    if (isSinglePlayer()) {
        this->createCollectable(collType, source, vel);
    }
}

void CDriver::requestBuildingTower(int type, QPointF pos) {
    if (isSinglePlayer()) {
        BuildingTower* t = Driver::createBuildingTower(type, pos);
        if (this->addToTower(t, human_) && t->isDone()) {
            this->createTower(t->getType(), t->getPos());
            this->destroyObject(t);
            human_->setResource(RESOURCE_NONE);
            return;
        }
    } else {
        Stream s;
        s.writeInt(human_->getID());
        s.writeInt(type);
        s.writeFloat(pos.x());
        s.writeFloat(pos.y());
        NetworkClient::instance()->send(network::kTowerChoice, s.data());
    }
}

void CDriver::requestSellTower(QPointF pos) {
    if (isSinglePlayer()) {
        Driver::sellTower(pos);
    } else {
        Stream s;
        s.writeFloat(pos.x());
        s.writeFloat(pos.y());
        NetworkClient::instance()->send(network::kSellTower, s.data());
    }
}

void CDriver::requestUpgradeTower(QPointF pos) {
    if (isSinglePlayer()) {
        Driver::upgradeTower(pos);
    } else {
        Stream s;
        s.writeFloat(pos.x());
        s.writeFloat(pos.y());
        NetworkClient::instance()->send(network::kUpgradeTower, s.data());
    }
}

void CDriver::NPCCreator() {
    timeCount_++;
    if(!waves_.empty()) {
        //disconnect(waveTimer_, SIGNAL(timeout()), this, SLOT(NPCCreator()));
        NPCWave* temp;
        foreach(temp,waves_) {
            if(temp->getStart() == timeCount_){
                temp->createWave();
                connect(temp, SIGNAL(waveDead()),this,SLOT(deadWave()));
            }
        }

        //waves_.first()->createWave();
        //connect((waves_.first()), SIGNAL(waveDead()),this,SLOT(deadWave()));
    }
}

void CDriver::startGame(bool singlePlayer) {
    // Create hard coded map
    gameMap_ = new Map(mainWindow_->getMD()->map(), this);
    gameTimer_ = new QTimer(this);
    waveTimer_ = new QTimer(this);
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

        Parser* fileParser = new Parser(this, MAP_NFO);
        NPCWave* tempWave;
        setBaseHealth(fileParser->baseHP);
        while((tempWave = fileParser->readWave())!=NULL) {
            waves_.append(tempWave);
        }

        waveTimer_->start(1000);
        connect(waveTimer_, SIGNAL(timeout()), this, SLOT(NPCCreator()));
        timeCount_ = 0;
    }

    //connect(mainWindow_,  SIGNAL(signalAltHeld(bool)),
            //npc_->getGraphicsComponent(), SLOT(showHealth(bool)));

    gameTimer_->start(GAME_TICK_INTERVAL);
}
void CDriver::deadWave(){
    if(!waves_.empty()) {
        /*disconnect((waves_.first()), SIGNAL(waveDead()),this,SLOT(deadWave()));
        waves_.takeFirst();
        connect(waveTimer_, SIGNAL(timeout()),this, SLOT(NPCCreator()));*/
    } else {
        endGame();
    }
}
void CDriver::endGame() {
    disconnectFromServer();
    this->waveTimer_->stop();
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
            buildContextMenu_->toggleMenu();
            break;

        case TILE_BUILT:
            towerContextMenu_->toggleMenu();
            break;

        case TILE_BASE:
            playerContextMenu_->toggleMenu();
            break;

        case TILE_RESOURCE:
            emit signalHarvesting(currentTile->getTiledTile()->id());
            break;

        default:
            emit signalDropResource();
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
        case network::kDropCollect:
        {
            unsigned int srcID = s->readInt();
            int type = s->readInt();

            float x = s->readFloat();
            float y = s->readFloat();
            QVector2D velocity(x, y);

            x = s->readFloat();
            y = s->readFloat();
            QPointF src(x, y);

            bool addToTower = s->readByte();

            if ((srcID & 0xFF000000) >> 24 == Player::clsIdx()) {
                Player* p = (Player*)mgr_->findObject(srcID);
                p->setResource(RESOURCE_NONE);
            }

            if (!addToTower) {
                Driver::createCollectable(type, src, velocity);
            }

            break;
        }
        case network::kPickCollect:
        {
            unsigned int playerID = s->readInt();
            unsigned int collID = s->readInt();

            if (playerID == human_->getID()) {
                break;
            }

            Player* p = (Player*)mgr_->findObject(playerID);
            Collectable* c = (Collectable*)mgr_->findObject(collID);

            p->pickupCollectable(p->getPos().x(), p->getPos().y(), c);

            break;
        }
        case network::kSellTower:
        {
            int actionType = s->readInt();
            float x = s->readFloat();
            float y = s->readFloat();

            Tile* tile = gameMap_->getTile(QPointF(x, y));
            tile->setActionType(actionType);

            break;
        }
        case network::kUpgradeTower:
        {
            float x = s->readFloat();
            float y = s->readFloat();

            Driver::upgradeTower(QPointF(x, y));

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
