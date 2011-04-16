#include <QtGui>
#include <QTimer>
#include <QApplication>
#include <QVector>
#include <QWidget>
#include "SDriver.h"
#include "Collectable.h"
#include "Player.h"
#include "Tower.h"
#include "NPCWave.h"
#include "Projectile.h"

#include "BuildingTower.h"

#include "Parser.h"


namespace td {

SDriver::SDriver() : Driver() {
    gameTimer_ = new QTimer(this);
    waveTimer_ = new QTimer(this);
    gameMap_ = new Map(MAP_TMX, this);
    net_ = new NetworkServer();
    npcCounter_ = 0;

    gameMap_->initMap();

    connect(net_, SIGNAL(msgReceived(Stream*)), 
            this, SLOT(onMsgReceive(Stream*)));

    connect(net_, SIGNAL(disconnected()),
            this, SIGNAL(disconnecting()));

    connect(net_, SIGNAL(socketDisconnect(QTcpSocket*)),
            this, SLOT(playerQuit(QTcpSocket*)));
}
SDriver::~SDriver() {
    if(!waves_.empty()) {
        NPCWave* temp;
        foreach(temp, waves_){
            disconnect((waves_.first()), SIGNAL(waveDead()),this,SLOT(deadWave()));
        }
    }
    delete net_;
}

unsigned int SDriver::addPlayer(QTcpSocket* sock, QString nickname) {
    mutex_.lock();
    net_->addConnection(sock);

    Player* p = (Player*)mgr_->createObject(Player::clsIdx());
    p->setNickname(nickname);
    players_.insert(sock, p);
    mutex_.unlock();

    return p->getID();
}

void SDriver::update(GameObject* obj) {
    updates_.insert(obj);
}

void SDriver::updateRT(GameObject* obj) {
    Stream s;
    obj->networkWrite(&s);

    net_->send(network::kPlayerPosition, s.data());
}

void SDriver::sendNetMessage(unsigned char msgType, QByteArray msg) {
    /* Enable if you need hex output for messages

    QString debug = "";

    for (int i = 0; i < msg.size(); i++) {
        QString tmp = QString().sprintf("%02X ", (unsigned char)msg.at(i));
        debug += tmp;
    }
    qDebug("%s", debug.toAscii().data());
    */

    net_->send(msgType, msg);
}

void SDriver::setBaseHealth(int health) {
    Driver::setBaseHealth(health);

    Stream s;
    s.writeInt(health);
    net_->send(network::kBaseHealth, s.data());

    if (health <= 0) {
        /* Base was slaughtered. You lose. */
        endGame(false);
    }
}

void SDriver::startGame(bool multicast) {
    Stream s;
    s.writeByte(players_.size());

    foreach (Player* user, players_.values()) {
        user->networkWrite(&s);
        user->resetDirty();
    }

    if (multicast) {
        /* Not "proper" but it saves space and the client can deal with it */
        s.writeByte(network::kMulticastIP);
        s.writeByte(net_->getMulticastAddr());
    }

    net_->send(network::kServerPlayers, s.data());

    Parser* fileParser = new Parser(this, MAP_NFO);
    NPCWave* tempWave;
    setBaseHealth(fileParser->baseHP);
    //tempWave = new NPCWave(this);
    //waves_.append(tempWave);
    while((tempWave = fileParser->readWave())!=NULL) {

        waves_.append(tempWave);
    }
    this->gameTimer_->start(30);
    this->waveTimer_->start(1000);
    connect(gameTimer_, SIGNAL(timeout()), this, SLOT(onTimerTick()));
    connect(waveTimer_, SIGNAL(timeout()), this, SLOT(spawnWave()));
}

void SDriver::endGame(bool success) {
    Stream send;
    send.writeByte(success);
    net_->send(network::kGameOver, send.data());

    net_->shutdown();
    this->gameTimer_->stop();
    this->waveTimer_->stop();
}

GameObject* SDriver::updateObject(Stream* s) {
    unsigned int id = s->readInt();

    GameObject* go = mgr_->findObject(id);
    if (go == NULL) {
        go = mgr_->createObjectWithID(id);
    } else if (go == (GameObject*)-1) {
        go = NULL;
    }

    if (go != NULL) {
        go->networkRead(s);
    }
    delete s;

    return go;
}

void SDriver::onTimerTick() {
    static unsigned int modcount = 0;
    if (modcount++ < 10) {
        return;
    }

    /* Reset the counter */
    modcount = 0;

    if (updates_.size() == 0) {
        return;
    }

    Stream s;
    s.writeShort(updates_.size());

    foreach (GameObject* go, updates_) {
        go->networkWrite(&s);
        go->resetDirty();
    }

    updates_.clear();

    net_->send(network::kServerUpdate, s.data());
}

void SDriver::destroyObject(GameObject* obj) {
    if (obj == (GameObject*)-1 || obj == NULL) {
        return;
    }

    int id = obj->getID();
    updates_.remove(obj);

    Driver::destroyObject(obj);

    Stream s;
    s.writeInt(id);

    net_->send(network::kDestroyObject, s.data());
}

void SDriver::destroyObject(int id) {
    GameObject* go = mgr_->findObject(id);
    if (go == (GameObject*)-1 || go == NULL) {
        return;
    }

    updates_.remove(go);

    Driver::destroyObject(id);

    Stream s;
    s.writeInt(id);

    net_->send(network::kDestroyObject, s.data());
}

void SDriver::spawnWave() {
    if(!waves_.empty()) {

        //disconnect(waveTimer_, SIGNAL(timeout()), this, SLOT(NPCCreator()));
        NPCWave* temp;
        foreach(temp,waves_) {
            if(temp->getStart() == timeCount_){
                temp->createWave();
                connect(temp, SIGNAL(waveDead()),this,SLOT(deadWave()));
            }
        }
    /*
    disconnect(waveTimer_, SIGNAL(timeout()), this, SLOT(spawnWave()));
    //NPCWave* wave = new NPCWave(this);


    waves_.first()->createWave();
    //waves_.append(wave);


    connect((waves_.first()), SIGNAL(waveDead()),this,SLOT(deadWave()));
    */
    }
}
void SDriver::deadWave(){
    if(!waves_.empty()) {
        /*disconnect((waves_.first()), SIGNAL(waveDead()),this,SLOT(deadWave()));
        waves_.takeFirst();
        connect(waveTimer_, SIGNAL(timeout()),this, SLOT(spawnWave()));*/
    } else {
        endGame(true);
    }
}

void SDriver::deadNPC(int id) {
    destroyObject(id);
}

void SDriver::requestProjectile(int projType, QPointF source,
        QPointF target, Unit* enemy) {
    Projectile* p = Driver::createProjectile(projType, source, target,     
            enemy);

    Stream s;
    p->networkWrite(&s);
    net_->send(network::kProjectile, s.data());
}

void SDriver::requestCollectable(int collType, QPointF source, QVector2D vel) {
    Collectable* c = Driver::createCollectable(collType, source, vel);

    Stream s;
    c->networkWrite(&s);
    net_->send(network::kCollectable, s.data());
}

void SDriver::towerDrop(BuildingTower* t, Player* player, bool drop) {
    Stream s;

    if (addToTower(t, player)) {
        if (t->isDone()) {
            Tower* tower = Driver::createTower(t->getType(),
                    t->getPos());
            updates_.insert(tower);
            destroyObject(t);
        } else {
            updates_.insert(t);
        }
        s.writeInt(player->getID());
        s.writeInt(player->getResource());
        s.writeFloat(0);
        s.writeFloat(0);
        s.writeFloat(player->getPos().x());
        s.writeFloat(player->getPos().y());
        s.writeByte(true);

        net_->send(network::kDropCollect, s.data());
    } else if (drop) {
        s.writeInt(player->getID());
        s.writeInt(player->getResource());
        QVector2D vel = this->getRandomVector();
        s.writeFloat(vel.x());
        s.writeFloat(vel.y());
        s.writeFloat(player->getPos().x());
        s.writeFloat(player->getPos().y());
        s.writeByte(false);

        net_->send(network::kDropCollect, s.data());
    }
}

void SDriver::onMsgReceive(Stream* s) {

    int message = s->readByte(); /* Message Type */
    GameObject* go = NULL;
    Stream* out = new Stream();

    switch(message) {
        case network::kSellTower:
        {
            float x = s->readFloat();
            float y = s->readFloat();

            Driver::sellTower(QPointF(x, y));

            out->writeInt(TILE_BUILDABLE);
            out->writeFloat(x);
            out->writeFloat(y);
            net_->send(network::kSellTower, out->data());

            break;
        }
        case network::kUpgradeTower:
        {
            float x = s->readFloat();
            float y = s->readFloat();

            if (Driver::upgradeTower(QPointF(x, y))) {
                out->writeFloat(x);
                out->writeFloat(y);
                net_->send(network::kUpgradeTower, out->data());
            }

            break;
        }
        case network::kTowerChoice:
        {
            int playerID = s->readInt();
            int towertype = s->readInt();
            float x = s->readFloat();
            float y = s->readFloat();

            Tile* currentTile = gameMap_->getTile(x, y);
            if (currentTile->getActionType() != TILE_BUILDABLE) {
                break;
            }

            Player* player = (Player*)mgr_->findObject(playerID);

            BuildingTower* t = Driver::createBuildingTower(towertype,
                    QPointF(x,y));

            updates_.insert(t);

            towerDrop(t, player, false);

            break;
        }
        case network::kDropCollect:
        {
            int playerID = s->readInt();
            int type = s->readInt();

            Player* player = (Player*)mgr_->findObject(playerID);
            Tile* currentTile = gameMap_->getTile(player->getPos().x(),
                                                  player->getPos().y());

            if (currentTile->getActionType() != TILE_BUILDING) {
                out->writeInt(playerID);
                out->writeInt(type);

                QVector2D vel = this->getRandomVector();
                out->writeFloat(vel.x());
                out->writeFloat(vel.y());

                out->writeFloat(player->getPos().x());
                out->writeFloat(player->getPos().y());

                out->writeByte(false);

                net_->send(network::kDropCollect, out->data());
            } else {
                BuildingTower* t = (BuildingTower*)currentTile->getExtension();
                towerDrop(t, player, true);
            }

            break;
        }
        case network::kConsoleChat:
        case network::kVoiceMessage:
        {
            QByteArray vc = s->read(s->size() - 1);
            net_->send(message, vc);
            break;
        }
        default:
        {
            go = this->updateObject(s);
            if (go == NULL) {
                break;
            }
            go->networkWrite(out);
            net_->send(network::kPlayerPosition, out->data());
            break;
        }
    }

    delete out;
}

void SDriver::playerQuit(QTcpSocket* sock) {
    Player* p = players_.value(sock);

    destroyObject(p);

    players_.remove(sock);
}

} /* end namespace td */
