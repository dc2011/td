#include <QtGui>
#include <QTimer>
#include <QApplication>
#include <QVector>
#include <QWidget>
#include "NPC.h"
#include "SDriver.h"

namespace td {

SDriver::SDriver() {
    waveTimer_ = new QTimer(this);
    mgr_ = new ResManager();
}

SDriver::~SDriver() {
    delete waveTimer_;
    delete mgr_;
}

void SDriver::startGame() {
    NetworkServer::init();
    connect(NetworkServer::instance(), SIGNAL(UDPReceived(Stream*)), 
		    this, SLOT(onUDPReceive(Stream*)));

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
void SDriver::onUDPReceive(Stream* s) {
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
