#include <QtGui>
#include <QTimer>
#include <QApplication>
#include <QVector>
#include <QWidget>
#include "NPC.h"
#include "Player.h"
#include "SDriver.h"

namespace td {

SDriver::SDriver() {
    waveTimer_ = new QTimer(this);
    mgr_ = new ResManager();
    net_ = new NetworkServer();

    connect(net_, SIGNAL(msgReceived(Stream*)), 
            this, SLOT(onMsgReceive(Stream*)));
}

SDriver::~SDriver() {
    delete net_;
    delete waveTimer_;
    delete mgr_;
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

    this->waveTimer_->start(15000);
    connect(waveTimer_, SIGNAL(timeout()), this, SLOT(spawnWave()));
}

void SDriver::endGame() {
    net_->shutdown();
    this->waveTimer_->stop();
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
void SDriver::destroyServerObj(int id) {
    Stream* out = new Stream();
    mgr_->deleteObject(id);
    out->writeInt(id);
    net_->send(network::kServerDestroyObj, out->data());
    delete out;
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
        case network::kClientDestroyObj:
        {
            int id = s->readInt();
            destroyServerObj(id);
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
