#include <QtGui>
#include <QTimer>
#include <QApplication>
#include <QVector>
#include <QWidget>
#include "NPC.h"
#include "Player.h"
#include "SDriver.h"

namespace td {

QMutex SDriver::mutex_;

SDriver::SDriver() {
    waveTimer_ = new QTimer(this);
    mgr_ = new ResManager();

    NetworkServer::init();
    connect(NetworkServer::instance(), SIGNAL(msgReceived(Stream*)), 
		    this, SLOT(onMsgReceive(Stream*)));
}

SDriver::~SDriver() {
    delete waveTimer_;
    delete mgr_;
}

void SDriver::addPlayer(QTcpSocket* sock, QString nickname) {
    mutex_.lock();
    NetworkServer::instance()->addConnection(sock);

    Player* p = (Player*)mgr_->createObject(Player::clsIdx());
    p->setNickname(nickname);
    mutex_.unlock();
}

void SDriver::startGame() {
    this->waveTimer_->start(15000);
    connect(waveTimer_, SIGNAL(timeout()), this, SLOT(spawnWave()));
}

void SDriver::endGame() {
    NetworkServer::shutdown();
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
    NetworkServer::instance()->send(network::kServerDestroyObj, out->data());
    delete out;
}
void SDriver::spawnWave() {
    qDebug("spawned wave");
    for(int i=0; i < 20; ++i) {
	    Stream* out = new Stream();
	    NPC* n;
	    n = (NPC*)mgr_->createObject(NPC::clsIdx());
	    n->networkWrite(out);
	    NetworkServer::instance()->send(network::kServerCreateObj, out->data());
	    delete out;
    }
}
void SDriver::onMsgReceive(Stream* s) {
    int message = s->readByte(); /* Message Type */
    GameObject* go = NULL;
    Stream* out = new Stream();

    switch(message) {
        case network::kRequestPlayerID:
        {
            unsigned char type = s->readByte();
            go = mgr_->createObject(type);
            out->writeInt(go->getID());
            NetworkServer::instance()->send(network::kAssignPlayerID,
                    out->data());
            break;
        }
        case network::kRequestTowerID:
	{
	    unsigned char type = s->readByte();
	    go = mgr_->createObject(type);
	    out->writeInt(go->getID());
	    NetworkServer::instance()->send(network::kAssignTowerID,
					    out->data());
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
            NetworkServer::instance()->send(network::kPlayerPosition,
                    out->data());
            break;
        }
    }

    delete out;
}

} /* end namespace td */
