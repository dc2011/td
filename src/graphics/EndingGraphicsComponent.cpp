
#include "EndingGraphicsComponent.h"

namespace td {

QPixmap* EndingGraphicsComponent::pixmapImgs_ = 0;

void EndingGraphicsComponent::update(GameObject*) {
    DrawParams* dp = new DrawParams();
    dp->pos = pos_;
    dp->degrees = 90;
    dp->scale = 1;
    emit signalDraw(dp, this, LAYER_DEFAULT);
}

void EndingGraphicsComponent::draw(void *dp, int layer) {
    GraphicsComponent::draw(dp, layer);
}

void EndingGraphicsComponent::animate() {
    if (!(animateCount_++ % animateMod_)) {
        ++pixmapIndex_ > arrayIndexMax_ ? pixmapIndex_ = arrayIndexMin_
            : pixmapIndex_;
        setImgIndex(pixmapIndex_);
    }
}

// cannon ending animation
QPixmap* CannonEndingGraphicsComponent::pixmapImgs_ = NULL;


void CannonEndingGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_END_CANNON_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_END_CANNON_0;
    pixmapImgs_[pixmapIndex_++] = PIX_END_CANNON_1;
    pixmapImgs_[pixmapIndex_++] = PIX_END_CANNON_2;
    setNonStaticValues();
}

void CannonEndingGraphicsComponent::setNonStaticValues() {
    animateMod_ = 3;
    arrayIndexMin_ = pixmapIndex_ = PIX_END_CANNON_START;
    arrayIndexMax_ = PIX_END_CANNON_START + PIX_END_CANNON_MAX - 1;
}

}
