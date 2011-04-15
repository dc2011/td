#include "EndingGraphicsComponentTypes.h"

namespace td {

// cannon ending animation

QPixmap* CannonEndingGraphicsComponent::pixmapImgs_ = NULL;

void CannonEndingGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_END_CANNON_MAX];
        pixmapIndex_ = 0;
        pixmapImgs_[pixmapIndex_++] = PIX_END_CANNON_0;
        pixmapImgs_[pixmapIndex_++] = PIX_END_CANNON_1;
        pixmapImgs_[pixmapIndex_++] = PIX_END_CANNON_2;
        setNonStaticValues();
    }

}
void CannonEndingGraphicsComponent::setNonStaticValues() {
    animateMod_ = PIX_END_CANNON_MAX;
    arrayIndexMin_ = pixmapIndex_ = PIX_END_CANNON_START;
    arrayIndexMax_ = PIX_END_CANNON_START + PIX_END_CANNON_MAX - 1;
    created_.release();
}

void CannonEndingGraphicsComponent::timerEvent(QTimerEvent*) {
    redraw(65, LAYER_FLYNPC);
}

// arrow
QPixmap* ArrowEndingGraphicsComponent::pixmapImgs_ = NULL;

void ArrowEndingGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_END_ARROW_MAX];
        pixmapIndex_ = 0;
        pixmapImgs_[pixmapIndex_++] = PIX_END_ARROW_0;
        setNonStaticValues();
    }

}
void ArrowEndingGraphicsComponent::setNonStaticValues() {
    animateMod_ = PIX_END_ARROW_MAX;
    arrayIndexMin_ = pixmapIndex_ = PIX_END_ARROW_START;
    arrayIndexMax_ = PIX_END_ARROW_START + PIX_END_ARROW_MAX - 1;
    created_.release();
}

void ArrowEndingGraphicsComponent::timerEvent(QTimerEvent*) {
    redraw(65, LAYER_FLYNPC);
}

// flying death

QPixmap* FlyingEndingGraphicsComponent::pixmapImgs_ = NULL;

void FlyingEndingGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_END_FLYING_MAX];
        pixmapIndex_ = 0;
        pixmapImgs_[pixmapIndex_++] = PIX_END_FLYING_0;
        pixmapImgs_[pixmapIndex_++] = PIX_END_FLYING_1;
        pixmapImgs_[pixmapIndex_++] = PIX_END_FLYING_2;
        pixmapImgs_[pixmapIndex_++] = PIX_END_FLYING_3;
        setNonStaticValues();
    }

}
void FlyingEndingGraphicsComponent::setNonStaticValues() {
    animateMod_ = PIX_END_FLYING_MAX;
    arrayIndexMin_ = pixmapIndex_ = PIX_END_FLYING_START;
    arrayIndexMax_ = PIX_END_FLYING_START + PIX_END_FLYING_MAX - 1;
    created_.release();
}

void FlyingEndingGraphicsComponent::timerEvent(QTimerEvent*) {
    redraw(1000, LAYER_DEFAULT);
}

// generic NPC death

QPixmap* GenericNPCEndingGraphicsComponent::pixmapImgs_ = NULL;

void GenericNPCEndingGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_END_GENERIC_MAX];
        pixmapIndex_ = 0;
        pixmapImgs_[pixmapIndex_++] = PIX_END_GENERIC_0;
        pixmapImgs_[pixmapIndex_++] = PIX_END_GENERIC_1;
        pixmapImgs_[pixmapIndex_++] = PIX_END_GENERIC_2;
        setNonStaticValues();
    }

}
void GenericNPCEndingGraphicsComponent::setNonStaticValues() {
    animateMod_ = PIX_END_GENERIC_MAX;
    arrayIndexMin_ = pixmapIndex_ = PIX_END_GENERIC_START;
    arrayIndexMax_ = PIX_END_GENERIC_START + PIX_END_GENERIC_MAX - 1;
    created_.release();
}

void GenericNPCEndingGraphicsComponent::timerEvent(QTimerEvent*) {
    redraw(1000, LAYER_DEFAULT);
}

}
