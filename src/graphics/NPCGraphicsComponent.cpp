#include "NPCGraphicsComponent.h"
#include "../engine/NPC.h"

namespace td {

NPCGraphicsComponent::NPCGraphicsComponent()
        : GraphicsComponent() {
    animateMod = 4;
    animateCount = 0;
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
    pixmapImgs[pixmapIndex++] = PIX_NPC_1;
    pixmapImgs[pixmapIndex++] = PIX_NPC_2;
    pixmapImgs[pixmapIndex++] = PIX_NPC_3;
    pixmapIndex = 0; //sets image back to start
}

void NPCGraphicsComponent::animate() {
    
    int pos;
    
    if (!isMoving_) {
        setImgIndex(pixmapIndex);
        return;
    }

    
    if (!(animateCount++ % animateMod)) {
        ++pixmapIndex >= PIX_NPC_MAX ? pixmapIndex = 0 : pixmapIndex;
        setImgIndex(pixmapIndex);
    }
}

void NPCGraphicsComponent::showHealth(bool keyHeld) {
    showHealth_ = keyHeld;
    qDebug("NPCGraphicsComponent::showHealth(); keyHeld = %d,", keyHeld);
}

} /* end namespace td */
