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
    initHealthbar();

    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_ANKLY_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_ANKLY_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_ANKLY_1;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_ANKLY_2;
    setNonStaticValues();
}

void NormNPCGraphicsComponent::setLayer(DrawParams* dp) {    
    emit signalDraw(dp, this, LAYER_NPC);
}

void NormNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_ANKLY_START;
    arrayIndexMax_ = PIX_NPC_ANKLY_START + PIX_NPC_ANKLY_MAX - 1;
}

void SlowNPCGraphicsComponent::initPixmaps() {
    initHealthbar();

    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_BRONTO_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_BRONTO_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_BRONTO_1;
    setNonStaticValues();
}

void SlowNPCGraphicsComponent::setLayer(DrawParams* dp) {    
    emit signalDraw(dp, this, LAYER_NPC);
}

void SlowNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_BRONTO_START;
    arrayIndexMax_ = PIX_NPC_BRONTO_START + PIX_NPC_BRONTO_MAX - 1;
}

void FastNPCGraphicsComponent::initPixmaps() {
    initHealthbar();

    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_SABER_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_SABER_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_SABER_1;
    setNonStaticValues();
}

void FastNPCGraphicsComponent::setLayer(DrawParams* dp) {    
    emit signalDraw(dp, this, LAYER_NPC);
}

void FastNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_SABER_START;
    arrayIndexMax_ = PIX_NPC_SABER_START + PIX_NPC_SABER_MAX - 1;
}

void FlyNPCGraphicsComponent::initPixmaps() {
    initHealthbar();

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

void FlyNPCGraphicsComponent::setLayer(DrawParams* dp) {
    emit signalDraw(dp, this, LAYER_FLYNPC);
}

void FlyNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_PTERO_START;
    arrayIndexMax_ = PIX_NPC_PTERO_START + PIX_NPC_PTERO_MAX - 1;
}

void BossNPCGraphicsComponent::initPixmaps() {
    initHealthbar();

    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_TREX_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_TREX_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_TREX_1;
    setNonStaticValues();
}

void BossNPCGraphicsComponent::setLayer(DrawParams* dp) {
    emit signalDraw(dp, this, LAYER_NPC);
}

void BossNPCGraphicsComponent::setNonStaticValues() {
    animateMod_ = 4;
    arrayIndexMin_ = pixmapIndex_ = PIX_NPC_TREX_START;
    arrayIndexMax_ = PIX_NPC_TREX_START + PIX_NPC_TREX_MAX - 1;
}

} /* end namespace td */
