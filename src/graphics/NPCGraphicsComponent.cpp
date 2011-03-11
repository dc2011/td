#include "NPCGraphicsComponent.h"
#include "../engine/NPC.h"

namespace td {

NPCGraphicsComponent::NPCGraphicsComponent()
        : GraphicsComponent() {
    animateMod_ = 4;
    animateCount_ = 0;
    animateConnect();
    emit created(this);
}

NPCGraphicsComponent::~NPCGraphicsComponent() {}

void NPCGraphicsComponent::update(GameObject* obj) {
    NPC* npc = (NPC*)obj;
    if (!npc->isDirty()) {//checks if object is dirty.
        return;
    }
    npc->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = npc->getPos();
    dp->moving  = 1;
    dp->degrees = npc->getOrientation();
    emit signalDraw(dp, this, LAYER_DEFAULT);
}

void NPCGraphicsComponent::showHealth(bool keyHeld) {
    showHealth_ = keyHeld;
    qDebug("NPCGraphicsComponent::showHealth(); keyHeld = %d,", keyHeld);
}

} /* end namespace td */
