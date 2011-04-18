#include "NPCGraphicsComponentTypes.h"
#include "../engine/CDriver.h"
#include "../engine/NPC.h"

namespace td {

/* Initialize the QPixmap arrays for all classes */
QPixmap* NormNPCGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* SlowNPCGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* ArmNPCGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FastNPCGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* SwarmNPCGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlyNPCGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* BossNPCGraphicsComponent::pixmapImgs_ = NULL;

void NormNPCGraphicsComponent::initPixmaps() {
    initHealthbar();
    setNonStaticValues();

    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_NORM_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_NORM_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_NORM_1;
    setNonStaticValues();
}

void NormNPCGraphicsComponent::setLayer(void* dp) {
    emit signalDraw(dp, this, LAYER_NPC);
}

void NormNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_NORM_START;
    arrayIndexMax_ = PIX_NPC_NORM_START + PIX_NPC_NORM_MAX - 1;
}

void SlowNPCGraphicsComponent::initPixmaps() {
    initHealthbar();
    setNonStaticValues();

    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_SLOW_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_BRONTO_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_BRONTO_1;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_BRONTO_2;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_BRONTO_3;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_BRONTO_4;
    setNonStaticValues();
}

void SlowNPCGraphicsComponent::setLayer(void* dp) {
    emit signalDraw(dp, this, LAYER_NPC);
}

void SlowNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_SLOW_START;
    arrayIndexMax_ = PIX_NPC_SLOW_START + PIX_NPC_SLOW_MAX - 1;
}

void ArmNPCGraphicsComponent::initPixmaps() {
    initHealthbar();
    setNonStaticValues();

    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_ARM_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_ARM_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_ARM_1;
    setNonStaticValues();
}

void ArmNPCGraphicsComponent::setLayer(void* dp) {
    emit signalDraw(dp, this, LAYER_NPC);
}

void ArmNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_ARM_START;
    arrayIndexMax_ = PIX_NPC_ARM_START + PIX_NPC_ARM_MAX - 1;
}

void FastNPCGraphicsComponent::initPixmaps() {
    initHealthbar();
    setNonStaticValues();

    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_FAST_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_FAST_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_FAST_1;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_FAST_2;
    setNonStaticValues();
}

void FastNPCGraphicsComponent::setLayer(void* dp) {
    emit signalDraw(dp, this, LAYER_NPC);
}

void FastNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_FAST_START;
    arrayIndexMax_ = PIX_NPC_FAST_START + PIX_NPC_FAST_MAX - 1;
}

void SwarmNPCGraphicsComponent::initPixmaps() {
    initHealthbar();
    setNonStaticValues();

    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_SWARM_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_SWARM_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_SWARM_1;
    setNonStaticValues();
}

void SwarmNPCGraphicsComponent::setLayer(void* dp) {
    emit signalDraw(dp, this, LAYER_NPC);
}

void SwarmNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_SWARM_START;
    arrayIndexMax_ = PIX_NPC_SWARM_START + PIX_NPC_SWARM_MAX - 1;
}

void FlyNPCGraphicsComponent::initPixmaps() {
    initHealthbar();
    setNonStaticValues();

    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_FLY_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_FLY_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_FLY_1;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_FLY_2;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_FLY_3;
    setNonStaticValues();
}

void FlyNPCGraphicsComponent::setLayer(void* dp) {
    emit signalDraw(dp, this, LAYER_FLYNPC);
}

void FlyNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_FLY_START;
    arrayIndexMax_ = PIX_NPC_FLY_START + PIX_NPC_FLY_MAX - 1;
}

void BossNPCGraphicsComponent::initPixmaps() {
    initHealthbar();
    setNonStaticValues();

    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_BOSS_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_TREX_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_TREX_1;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_TREX_2;
    setNonStaticValues();
}

void BossNPCGraphicsComponent::setLayer(void* dp) {
    emit signalDraw(dp, this, LAYER_NPC);
}

void BossNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_BOSS_START;
    arrayIndexMax_ = PIX_NPC_BOSS_START + PIX_NPC_BOSS_MAX - 1;
}

} /* end namespace td */
