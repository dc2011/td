#include "NPCWave.h"
#include "Driver.h"
#ifdef SERVER
#    include "SDriver.h"
#endif

namespace td {

NPCWave::NPCWave(QObject* parent) : GameObject(parent), start_(10),
        count_(5), type_(NPC_NORM), created_(0) {
}

NPCWave::NPCWave(QObject* parent, unsigned int start, unsigned int count,
        unsigned int type) : GameObject(parent), start_(start), 
        count_(count), type_(type), created_(0) {
}

NPCWave::~NPCWave() { }

void NPCWave::createWave() {
    created_ = 1;

    /*NPC* npc = getDriver()->createNPC(type_);
    children_.insert(npc);*/
}

void NPCWave::update() {
    static unsigned int tickmod = 0;
    if (created_ < count_ && (++tickmod % 30) == 0) {
        created_++;
        // create an NPC
    }

    Stream s;
    s.writeInt(children_.size());
    foreach (NPC* npc, children_) {
        npc->update();
        npc->networkWrite(&s);
    }
}

}
