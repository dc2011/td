#include "NPCGraphicsComponent.h"
#include "../engine/Player.h"

NPCGraphicsComponent::NPCGraphicsComponent()
        : GraphicsComponent() {
    emit created(this);
}

NPCGraphicsComponent::~NPCGraphicsComponent() {}

void NPCGraphicsComponent::update(GameObject* obj) {
    Player* npc = (Player*)obj;
    if (!npc->isDirty()) {//checks if object is dirty.
        return;
    }
    npc->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = npc->getPos();
    dp->moving  = 1; //is always moving
    //player->getVelocity().length() != 0;
    //dp->scale   = npc->getScale(); // will likely be a constant value here
    dp->degrees = npc->getOrientation();
    emit signalDraw(dp, this);
}

void NPCGraphicsComponent::initPixmaps() {
    //TODO: add animation images here
    pixmapImgs = new QPixmap[PIX_NPC_MAX];
    pixmapIndex = 0;
    pixmapImgs[pixmapIndex++] = PIX_NPC_0;
    pixmapIndex = 0; //sets image back to start
}
