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
    }

    go->networkRead(s);
    delete s;

    return go;
}

void SDriver::onUDPReceive(Stream* s) {
    s->readByte(); /* Message Type */

    GameObject* obj = updateObject(s);

    Stream* out = new Stream();
    obj->networkWrite(out);
    NetworkServer::instance()->send(network::kPlayerPosition, out->data()); 
    delete out;
}

} /* end namespace td */
