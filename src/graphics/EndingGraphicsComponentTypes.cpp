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
}

void CannonEndingGraphicsComponent::timerEvent(QTimerEvent*) {
           if (currentIndex_++ > arrayIndexMax_ + 1) {
               this->killTimer(timerID_);
               this->deleteComponent();
               return;
           }
           DrawParams* dp = new DrawParams();
           dp->pos = this->pos_;
           this->draw(dp, LAYER_FLYNPC);
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
}

void ArrowEndingGraphicsComponent::timerEvent(QTimerEvent*) {
           if (currentIndex_++ > arrayIndexMax_ + 5) {
               this->killTimer(timerID_);
               this->deleteComponent();
               return;
           }
           DrawParams* dp = new DrawParams();
           dp->scale = currentIndex_ / 6.0;
           dp->pos = this->pos_;
           this->draw(dp, LAYER_FLYNPC);
}

}
