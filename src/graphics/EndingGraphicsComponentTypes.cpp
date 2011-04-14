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


}
