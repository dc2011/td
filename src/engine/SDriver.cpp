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

void SDriver::startGame() {
    Stream s;
    s.writeByte(players_.size());

    foreach (Player* user, players_) {
        user->networkWrite(&s);
        user->resetDirty();
    }

    net_->send(network::kServerPlayers, s.data());

    this->gameTimer_->start(15000);
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

void SDriver::destroyObject(GameObject* obj) {
    int id = obj->getID();
    Driver::destroyObject(obj);

    Stream s;
    s.writeInt(id);

    net_->send(network::kDestroyObject, s.data());
}

void SDriver::destroyObject(int id) {
    Driver::destroyObject(id);

    Stream s;
    s.writeInt(id);

    net_->send(network::kDestroyObject, s.data());
}

Tower* SDriver::createTower(int type) {
    Tower* tower = (Tower*)mgr_->createObject(Tower::clsIdx());

    tower->setType(type);

    tower->initComponents();

    return tower;
}

/*NPC* SDriver::createNPC(int type) {
}*/

/*Resource* SDriver::createResource(int type) {
}*/

void SDriver::spawnWave() {
    qDebug("spawned wave");
    for(int i=0; i < 20; ++i) {
	    Stream* out = new Stream();
	    NPC* n;
	    n = (NPC*)mgr_->createObject(NPC::clsIdx());
	    n->networkWrite(out);
	    net_->send(network::kServerCreateObj, out->data());
	    delete out;
    }
}

void SDriver::deadNPC(int id) {
    destroyObject(id);
}


void SDriver::onMsgReceive(Stream* s) {

    int message = s->readByte(); /* Message Type */
    GameObject* go = NULL;
    Stream* out = new Stream();

    switch(message) {
        case network::kRequestTowerID:
        {
            unsigned char type = s->readByte();
            go = mgr_->createObject(type);
            out->writeInt(go->getID());
            net_->send(network::kAssignTowerID, out->data());
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
