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
    gameMap_ = new Map(QString("./maps/netbookmap3.tmx"), this);
    net_ = new NetworkServer();
    npcCounter_ = 0;

    connect(net_, SIGNAL(msgReceived(Stream*)), 
            this, SLOT(onMsgReceive(Stream*)));

    connect(net_, SIGNAL(disconnected()),
            this, SIGNAL(disconnecting()));
}
SDriver::~SDriver() {
    disconnect((waves_.first()), SIGNAL(waveDead()),this,SLOT(deadWave()));
    delete net_;
}

unsigned int SDriver::addPlayer(QTcpSocket* sock, QString nickname) {
    mutex_.lock();
    net_->addConnection(sock);

    Player* p = (Player*)mgr_->createObject(Player::clsIdx());
    p->setNickname(nickname);
    players_.append(p);
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
        Stream send;
        send.writeByte(false);
        net_->send(network::kGameOver, send.data());
    }
}

void SDriver::startGame(bool multicast) {
    Stream s;
    s.writeByte(players_.size());

    foreach (Player* user, players_) {
        user->networkWrite(&s);
        user->resetDirty();
    }

    if (multicast) {
        /* Not "proper" but it saves space and the client can deal with it */
        s.writeByte(network::kMulticastIP);
        s.writeByte(net_->getMulticastAddr());
    }

    net_->send(network::kServerPlayers, s.data());

    gameMap_->initMap();

    Parser* fileParser = new Parser(this, "./maps/mapinfo.nfo");
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

void SDriver::endGame() {
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
    disconnect(waveTimer_, SIGNAL(timeout()), this, SLOT(spawnWave()));
    //NPCWave* wave = new NPCWave(this);


    waves_.first()->createWave();
    //waves_.append(wave);


    connect((waves_.first()), SIGNAL(waveDead()),this,SLOT(deadWave()));

    }
    /*if (npcCounter_++ % 15 == 0 && (npcCounter_ % 400) > 300) {
        Driver::createNPC(NPC_NORM);
    }
    if (npcCounter_ % 40 == 0 && (npcCounter_ % 1400) > 1000) {
        Driver::createNPC(NPC_SLOW);
    }*/

    /*qDebug("spawned wave");
    for(int i=0; i < 20; ++i) {
	    Stream* out = new Stream();
	    NPC* n;
	    n = (NPC*)mgr_->createObject(NPC::clsIdx());
        n->setType(NPC_NORM);
	    n->networkWrite(out);
	    net_->send(network::kServerCreateObj, out->data());
	    delete out;
    }*/
}
void SDriver::deadWave(){
    if(!waves_.empty()) {
        disconnect((waves_.first()), SIGNAL(waveDead()),this,SLOT(deadWave()));
        waves_.takeFirst();
        connect(waveTimer_, SIGNAL(timeout()),this, SLOT(spawnWave()));
    } else {
        endGame();
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

void SDriver::towerDrop(Stream* out, BuildingTower* t, Player* player) {
    if (addToTower(t, player)) {
        if (t->isDone()) {
            Tower* tower = Driver::createTower(t->getType(),
                    t->getPos());
            updates_.insert(tower);
            destroyObject(t);
        } else {
            updates_.insert(t);
        }
        out->writeInt(player->getID());
        out->writeInt(true);
    } else {
        out->writeInt(player->getID());
        out->writeInt(false);
    }
    net_->send(network::kDropResource, out->data());
}

void SDriver::onMsgReceive(Stream* s) {

    int message = s->readByte(); /* Message Type */
    GameObject* go = NULL;
    Stream* out = new Stream();

    switch(message) {
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

            towerDrop(out, t, player);

            break;
        }
        case network::kDropResource:
        {
            int playerID = s->readInt();
            float x = s->readFloat();
            float y = s->readFloat();

            Player* player = (Player*)mgr_->findObject(playerID);

            Tile* currentTile = gameMap_->getTile(x, y);
            if (currentTile->getActionType() != TILE_BUILDING) {
                out->writeInt(player->getID());
                out->writeInt(false);
	            net_->send(network::kDropResource, out->data());
                break;
            }
            
            BuildingTower* t = (BuildingTower*)currentTile->getExtension();

            towerDrop(out, t, player);

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

} /* end namespace td */
