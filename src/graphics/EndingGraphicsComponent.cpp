
#include "EndingGraphicsComponent.h"

namespace td {

void EndingGraphicsComponent::update(GameObject*) {
    DrawParams* dp = new DrawParams();

    emit signalDraw(dp, this, LAYER_DEFAULT);
}

void EndingGraphicsComponent::draw(DrawParams *dp, int layer) {
    GraphicsComponent::draw(dp, layer);
}

void EndingGraphicsComponent::animate() {
    if(animateMod_ == 0) {
        return;
    }
    if (!(animateCount_++ % animateMod_)) {
        ++pixmapIndex_ > arrayIndexMax_ ? pixmapIndex_ = arrayIndexMin_
            : pixmapIndex_;
        setImgIndex(pixmapIndex_);
    }
}

void EndingGraphicsComponent::redraw(int timerLength, int layer) {
    created_.acquire();

    if (timerID_ != 0) {
        killTimer(timerID_);
    }
    timerID_ = this->startTimer(timerLength);

    if (currentIndex_++ > arrayIndexMax_ + 1) {
       this->killTimer(timerID_);
       this->deleteComponent();
       return;
    }
    DrawParams* dp = new DrawParams();
    dp->pos = this->pos_;
    this->draw(dp, LAYER_DEFAULT);

    created_.release();
}

}
