#include "NPCWave.h"
#include "Driver.h"
#include "./audio/SfxManager.h"
#include "../network/netmessages.h"

namespace td {

NPCWave::NPCWave(QObject* parent) : QObject(parent), start_(10),
        count_(5), type_(NPC_NORM), created_(0), pathNum_(0), gemCount_(0) {
}

NPCWave::NPCWave(QObject* parent, unsigned int start, unsigned int count,
        unsigned int type, unsigned int path, unsigned int gems) : QObject(parent),
    start_(start), count_(count), type_(type), created_(0), pathNum_(path),
    gemCount_(gems) {
}

NPCWave::~NPCWave() {
    children_.clear();
}

void NPCWave::createWave() {


    PLAY_SFX(this, SfxManager::npcPterodactylEnters);


    connect(getDriver()->getTimer(), SIGNAL(timeout()),
            this, SLOT(update()));

}

void NPCWave::killChild(NPC* child) {
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

    // TODO: Some actual logic here to fix this
    if (created_ < count_ && ++tickmod % 15 == 0) {
        created_++;

        NPC* npc = getDriver()->createNPC(type_);
        npc->setWave(this);

        ((NPCInputComponent*)npc->getInputComponent())->initWaypoints(pathNum_);

        children_.insert(npc);

    }
#ifdef SERVER
    Stream s;
    s.writeShort(children_.size());
    #endif
    foreach (NPC* npc, children_) {
        npc->update();
        #ifdef SERVER
        npc->networkWrite(&s);
        #endif
    }
#ifdef SERVER
    getDriver()->sendNetMessage(network::kNPCWave, s.data());
#endif
}

}
