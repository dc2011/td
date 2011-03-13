#include "NPCGraphicsComponent.h"
#include "../engine/NPC.h"

namespace td {

QPixmap * NPCGraphicsComponent::pixmapImgs_ = 0;

NPCGraphicsComponent::NPCGraphicsComponent()
        : GraphicsComponent() {
}

NPCGraphicsComponent::NPCGraphicsComponent(int npcType)
    : GraphicsComponent(), npcType_(npcType) {
    emit created(this);
}

NPCGraphicsComponent::~NPCGraphicsComponent() {}

void NPCGraphicsComponent::update(GameObject* obj) {
    NPC* npc = (NPC*)obj;
    if (!npc->isDirty()) {
        return;
    }
    npc->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = npc->getPos();
    dp->moving  = 1;
    dp->degrees = npc->getOrientation();
    
    //TODO: the layers will change with different NPC's
    emit signalDraw(dp, this, LAYER_FLYNPC);
}

void NPCGraphicsComponent::showHealth(bool keyHeld) {
    showHealth_ = keyHeld;
}

void NPCGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_TOTAL];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_1;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_2;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_3;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PLEA_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PLEA_1;
    setNonStaticValues();
}

void NPCGraphicsComponent::setNonStaticValues() {
    switch (npcType_) {
    case NPC_PTERO:
        animateMod_ = 4;
        arrayIndexMin_ = pixmapIndex_ = PIX_NPC_PTERO_START;
        arrayIndexMax_ = PIX_NPC_PTERO_START + PIX_NPC_PTERO_MAX - 1;

        break;
    case NPC_PLEA:
        animateMod_ = 6;
        arrayIndexMin_ = pixmapIndex_ = PIX_NPC_PLEA_START;
        arrayIndexMax_ = PIX_NPC_PLEA_START + PIX_NPC_PLEA_MAX - 1;
        break;
    }
}

QPixmap * NPCGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

void NPCGraphicsComponent::animate() {
    if (!(animateCount_++ % animateMod_)) {
        ++pixmapIndex_ > arrayIndexMax_ ? pixmapIndex_ = arrayIndexMin_
            : pixmapIndex_;
        setImgIndex(pixmapIndex_);

    }
}

} /* end namespace td */
