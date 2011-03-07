#include <QtGui>
#include <QTimer>
#include <QApplication>
#include <QVector>
#include <QWidget>
#include "SDriver.h"

namespace td {

SDriver::SDriver() {
    gameTimer_ = new QTimer(this);
    mgr_ = new ResManager();
}

SDriver::~SDriver() {
    delete gameTimer_;
    delete mgr_;
}

void SDriver::startGame() {
    NetworkServer::init();
    connect(NetworkServer::instance(), SIGNAL(UDPReceived(Stream*)), 
		    this, SLOT(onUDPReceive(Stream*)));

    this->gameTimer_->start(50);
}

void SDriver::endGame() {
    NetworkServer::shutdown();
    this->gameTimer_->stop();
}

GameObject* SDriver::updateObject(Stream* s) {
    unsigned int id = s->readInt();

    GameObject* go = mgr_->findObject(id);
    if (go == NULL) {
        go = mgr_->createObject((id & 0xFF000000) >> 24);
        go->setID(id);
        mgr_->addExistingObject(go);
    }

    go->networkRead(s);
    delete s;

    return go;
}

void SDriver::onUDPReceive(Stream* s) {
    int message = s->readByte(); /* Message Type */
    GameObject* go = NULL;
    Stream* out = new Stream();

    switch(message) {
        case network::kRequestObjID:
        {
            unsigned char type = s->readByte();
            go = mgr_->createAddObject(type);
            out->writeInt(go->getID());
            NetworkServer::instance()->send(network::kAssignObjID,
                    out->data());
            break;
        }
        default:
        {
            go = this->updateObject(s);
            go->networkWrite(out);
            NetworkServer::instance()->send(network::kPlayerPosition,
                    out->data());
            break;
        }
    }

    delete out;
}

} /* end namespace td */
