#include "NPCWave.h"
#include "Driver.h"
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
    created_ = 1;

    NPC* npc = getDriver()->createNPC(type_);
    npc->setWave(this);
    children_.insert(npc);

    connect(getDriver()->getTimer(), SIGNAL(timeout()),
            this, SLOT(update()));
}

void NPCWave::killChild(NPC* child) {
    children_.remove(child);
}

void NPCWave::update() {
    static unsigned int tickmod = 0;
    // TODO: Some actual logic here to fix this
    if (created_ < count_ && ++tickmod % 15 == 0) {
        created_++;

        NPC* npc = getDriver()->createNPC(type_);
        npc->setWave(this);
        children_.insert(npc);
    }

    Stream s;
    s.writeShort(children_.size());
    foreach (NPC* npc, children_) {
        npc->update();
        npc->networkWrite(&s);
    }

    getDriver()->sendNetMessage(network::kNPCWave, s.data());
}

}
