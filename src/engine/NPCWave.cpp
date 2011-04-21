#include "NPCWave.h"
#include "CDriver.h"
#include "Driver.h"
#include "./audio/SfxManager.h"
#include "../network/netmessages.h"

namespace td {

NPCWave::NPCWave(QObject* parent) : QObject(parent), start_(10),
        count_(5), type_(NPC_NORM), created_(0), pathNum_(0), gemCount_(0) , density_(15){
}

NPCWave::NPCWave(QObject* parent, unsigned int start, unsigned int count,
        unsigned int type, unsigned int path, unsigned int gems,
        unsigned int density) : QObject(parent),
    start_(start), count_(count), type_(type), created_(0), pathNum_(path),
    gemCount_(gems), density_(density) {
}

NPCWave::~NPCWave() {
    foreach(NPC* child, children_){
        delete child;
    }
    //children_.clear();
}

void NPCWave::createWave() {
    connect(getDriver()->getTimer(), SIGNAL(timeout()),
            this, SLOT(update()));
}

void NPCWave::killChild(NPC* child) {
#ifndef SERVER
    disconnect(CDriver::instance()->getMainWindow(),  SIGNAL(signalAltHeld(bool)),
            child->getGraphicsComponent(), SLOT(showHealth(bool)));
#endif
    children_.remove(child);

    if (isDead()) {

        emit waveDead();
    }
}

void NPCWave::update() {

    static unsigned int tickmod = 0;
    static unsigned int sfxdelay = 0;
    if (++sfxdelay < 130) {
        return;
    }

    if (created_ < count_ && ++tickmod % density_ == 0) {
        created_++;

        NPC* npc = getDriver()->createNPC(type_);
        npc->setWave(this);

        ((NPCInputComponent*)npc->getInputComponent())->initWaypoints(pathNum_);
#ifndef SERVER
        connect(CDriver::instance()->getMainWindow(),  SIGNAL(signalAltHeld(bool)),
                npc->getGraphicsComponent(), SLOT(showHealth(bool)));
#endif
        children_.insert(npc);
    }

    Stream s;
    s.writeShort(children_.size());
    foreach (NPC* npc, children_) {
        npc->update();
        npc->networkWrite(&s);
    }
#ifdef SERVER
    getDriver()->sendNetMessage(network::kNPCWave, s.data());
#endif
}

}
