#include <QtGui>
#include <QTimer>
#include <QApplication>
#include <QVector>
#include <QWidget>
#include "SDriver.h"
#include "Player.h"
#include "Tower.h"
#include "NPC.h"
#include "Resource.h"

namespace td {

SDriver::SDriver() : Driver() {
    gameTimer_ = new QTimer(this);
    gameMap_ = new Map(QString("./maps/netbookmap2.tmx"));
    net_ = new NetworkServer();

    connect(net_, SIGNAL(msgReceived(Stream*)), 
            this, SLOT(onMsgReceive(Stream*)));
}
SDriver::~SDriver() {
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

void SDriver::startGame() {
    Stream s;
    s.writeByte(players_.size());

    foreach (Player* user, players_) {
        user->networkWrite(&s);
        user->resetDirty();
    }

    net_->send(network::kServerPlayers, s.data());

    gameMap_->initMap();

    this->gameTimer_->start(30);
    connect(gameTimer_, SIGNAL(timeout()), this, SLOT(onTimerTick()));
    connect(gameTimer_, SIGNAL(timeout()), this, SLOT(spawnWave()));
}

void SDriver::endGame() {
    net_->shutdown();
    this->gameTimer_->stop();
}

GameObject* SDriver::updateObject(Stream* s) {
    unsigned int id = s->readInt();

    GameObject* go = mgr_->findObject(id);
    if (go == NULL) {
        go = mgr_->createObjectWithID(id);
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
    int id = obj->getID();
    updates_.remove(obj);

    Driver::destroyObject(obj);

    Stream s;
    s.writeInt(id);

    net_->send(network::kDestroyObject, s.data());
}

void SDriver::destroyObject(int id) {
    GameObject* go = mgr_->findObject(id);
    updates_.remove(go);

    Driver::destroyObject(id);

    Stream s;
    s.writeInt(id);

    net_->send(network::kDestroyObject, s.data());
}

Tower* SDriver::createTower(int type) {
    Tower* tower = (Tower*)mgr_->createObject(Tower::clsIdx());

    tower->setType(type);
    tower->initComponents();

    connect(gameTimer_, SIGNAL(timeout()), tower, SLOT(update()));

    return tower;
}

NPC* SDriver::createNPC(int type) {
    NPC* npc = (NPC*)mgr_->createObject(NPC::clsIdx());

    npc->setType(type);
    npc->initComponents();

    connect(gameTimer_, SIGNAL(timeout()), npc, SLOT(update()));

    return npc;
}

/*Resource* SDriver::createResource(int type) {
}*/

void SDriver::spawnWave() {
    if (npcCounter_++ % 15 == 0 && (npcCounter_ % 400) > 300) {
        createNPC(NPC_NORM);
    }
    if (npcCounter_ % 40 == 0 && (npcCounter_ % 1400) > 1000) {
        createNPC(NPC_SLOW);
    }

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

void SDriver::deadNPC(int id) {
    destroyObject(id);
}


void SDriver::onMsgReceive(Stream* s) {

    int message = s->readByte(); /* Message Type */
    GameObject* go = NULL;
    Stream* out = new Stream();

    switch(message) {
        case network::kBuildTower:
        {
            int playerID = s->readInt();
            int towertype = s->readInt();
            float x = s->readFloat();
            float y = s->readFloat();

            Player* player = (Player*)mgr_->findObject(playerID);
            if (player->getPos().x() != x || player->getPos().y() != y) {
                break;
            }

            Tile* currentTile = gameMap_->getTile(x, y);
            if (currentTile->getActionType() != TILE_BUILDABLE) {
                break;
            }

            Tower* t = createTower(towertype);
            t->setPos(currentTile->getPos());
            currentTile->setExtension(t);

            updates_.insert(t);
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
