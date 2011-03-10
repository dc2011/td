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

void NPCGraphicsComponent::initPixmaps() {
    //TODO: add animation images here
    pixmapImgs_ = new QPixmap[PIX_NPC_MAX];
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_1;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_2;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_3;
    pixmapIndex_ = 0; //sets image back to start
}

void NPCGraphicsComponent::animate() {
    if (!isMoving_) {
        setImgIndex(pixmapIndex_);
        return;
    }

    
    if (!(animateCount_++ % animateMod_)) {
        ++pixmapIndex_ >= PIX_NPC_MAX ? pixmapIndex_ = 0 : pixmapIndex_;
        setImgIndex(pixmapIndex_);
    }
}

void NPCGraphicsComponent::showHealth(bool keyHeld) {
    showHealth_ = keyHeld;
    qDebug("NPCGraphicsComponent::showHealth(); keyHeld = %d,", keyHeld);
}

} /* end namespace td */
