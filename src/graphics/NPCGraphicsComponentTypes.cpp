#include "NPCGraphicsComponentTypes.h"
#include "../engine/CDriver.h"
#include "../engine/NPC.h"

namespace td {

/* Initialize the QPixmap arrays for all classes */
QPixmap* NormNPCGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* SlowNPCGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FastNPCGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlyNPCGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* BossNPCGraphicsComponent::pixmapImgs_ = NULL;

//TODO: need pics and animation for this yet
void NormNPCGraphicsComponent::initPixmaps() {
    healthbarItem_ = new QGraphicsRectItem(QRectF(OFFSCREEN, OFFSCREEN, 96, 7));
    npcHealth = 1;
    CDriver::instance()->getMainWindow()->getScene()->addItem(healthbarItem_);
    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_PTERO_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_1;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_2;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_3;
    setNonStaticValues();
}

void NormNPCGraphicsComponent::update(GameObject* obj) {
    NPC* npc = (NPC*)obj;
    if (!npc->isDirty()) {
        return;
    }
    npc->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = npc->getPos();
    dp->moving  = 1;
    dp->degrees = npc->getOrientation();
    //npcHealth   = (npc->getHealth()/npc->getMaxHealth()); This is the real thing. Commented until damage works.
    npcHealth   = npcHealth - 0.003; //This and the following lines are for tests.
    if(npcHealth < 0) {
        npcHealth = 0;
    }
    
    emit signalDraw(dp, this, LAYER_NPC);
}

void NormNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_PTERO_START;
    arrayIndexMax_ = PIX_NPC_PTERO_START + PIX_NPC_PTERO_MAX - 1;
}

//TODO: need pics and animation for this yet
void SlowNPCGraphicsComponent::initPixmaps() {
    healthbarItem_ = new QGraphicsRectItem(QRectF(OFFSCREEN, OFFSCREEN, 96, 7));
    npcHealth = 1;
    CDriver::instance()->getMainWindow()->getScene()->addItem(healthbarItem_);
    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_PLEA_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PLEA_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PLEA_1;
    setNonStaticValues();
}

void SlowNPCGraphicsComponent::update(GameObject* obj) {
    NPC* npc = (NPC*)obj;
    if (!npc->isDirty()) {
        return;
    }
    npc->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = npc->getPos();
    dp->moving  = 1;
    dp->degrees = npc->getOrientation();
    //npcHealth   = (npc->getHealth()/npc->getMaxHealth()); This is the real thing. Commented until damage works.
    npcHealth   = npcHealth - 0.003; //This and the following lines are for tests.
    if(npcHealth < 0) {
        npcHealth = 0;
    }
    
    emit signalDraw(dp, this, LAYER_NPC);
}

void SlowNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_PLEA_START;
    arrayIndexMax_ = PIX_NPC_PLEA_START + PIX_NPC_PLEA_MAX - 1;
}

//TODO: need pics and animation for this yet
void FastNPCGraphicsComponent::initPixmaps() {
    healthbarItem_ = new QGraphicsRectItem(QRectF(OFFSCREEN, OFFSCREEN, 96, 7));
    npcHealth = 1;
    CDriver::instance()->getMainWindow()->getScene()->addItem(healthbarItem_);
    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_PTERO_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_1;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_2;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_3;
    setNonStaticValues();
}

void FastNPCGraphicsComponent::update(GameObject* obj) {
    NPC* npc = (NPC*)obj;
    if (!npc->isDirty()) {
        return;
    }
    npc->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = npc->getPos();
    dp->moving  = 1;
    dp->degrees = npc->getOrientation();
    //npcHealth   = (npc->getHealth()/npc->getMaxHealth()); This is the real thing. Commented until damage works.
    npcHealth   = npcHealth - 0.003; //This and the following lines are for tests.
    if(npcHealth < 0) {
        npcHealth = 0;
    }
    
    emit signalDraw(dp, this, LAYER_NPC);
}

void FastNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_PTERO_START;
    arrayIndexMax_ = PIX_NPC_PTERO_START + PIX_NPC_PTERO_MAX - 1;
}

void FlyNPCGraphicsComponent::initPixmaps() {
    healthbarItem_ = new QGraphicsRectItem(QRectF(OFFSCREEN, OFFSCREEN, 96, 7));
    npcHealth = 1;
    CDriver::instance()->getMainWindow()->getScene()->addItem(healthbarItem_);
    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_PTERO_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_1;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_2;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_3;
    setNonStaticValues();
}

void FlyNPCGraphicsComponent::update(GameObject* obj) {
    NPC* npc = (NPC*)obj;
    if (!npc->isDirty()) {
        return;
    }
    npc->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = npc->getPos();
    dp->moving  = 1;
    dp->degrees = npc->getOrientation();
    //npcHealth   = (npc->getHealth()/npc->getMaxHealth()); This is the real thing. Commented until damage works.
    npcHealth   = npcHealth - 0.003; //This and the following lines are for tests.
    if(npcHealth < 0) {
        npcHealth = 0;
    }
    
    emit signalDraw(dp, this, LAYER_FLYNPC);
}

void FlyNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_PTERO_START;
    arrayIndexMax_ = PIX_NPC_PTERO_START + PIX_NPC_PTERO_MAX - 1;
}

//TODO: need pics and animation for this yet
void BossNPCGraphicsComponent::initPixmaps() {
    healthbarItem_ = new QGraphicsRectItem(QRectF(OFFSCREEN, OFFSCREEN, 96, 7));
    npcHealth = 1;
    CDriver::instance()->getMainWindow()->getScene()->addItem(healthbarItem_);
    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_PTERO_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_1;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_2;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_3;
    setNonStaticValues();
}

void BossNPCGraphicsComponent::update(GameObject* obj) {
    NPC* npc = (NPC*)obj;
    if (!npc->isDirty()) {
        return;
    }
    npc->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = npc->getPos();
    dp->moving  = 1;
    dp->degrees = npc->getOrientation();
    //npcHealth   = (npc->getHealth()/npc->getMaxHealth()); This is the real thing. Commented until damage works.
    npcHealth   = npcHealth - 0.003; //This and the following lines are for tests.
    if(npcHealth < 0) {
        npcHealth = 0;
    }
    
    emit signalDraw(dp, this, LAYER_NPC);
}

void BossNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_PTERO_START;
    arrayIndexMax_ = PIX_NPC_PTERO_START + PIX_NPC_PTERO_MAX - 1;
}

} /* end namespace td */
