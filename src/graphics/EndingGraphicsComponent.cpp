#include "EndingGraphicsComponent.h"

namespace td {

EndingGraphicsComponent::EndingGraphicsComponent(const QPointF& pos,
        const int layer, const int timerLength)
        : GraphicsComponent(), arrayIndexMin_(0), arrayIndexMax_(0),
          currentIndex_(0), timerID_(0),  pos_(pos), created_(0), layer_(layer),
          timerLength_(timerLength) {
}

void EndingGraphicsComponent::update(GameObject*) {
    if (timerID_ != 0) {
        killTimer(timerID_);
    }
    timerID_ = this->startTimer(timerLength_);

    if (currentIndex_++ > arrayIndexMax_ + 1) {
       this->killTimer(timerID_);
       this->deleteComponent();
       return;
    }

    DrawParams* dp = new DrawParams();
    dp->pos = pos_;
    dp->degrees = 90;
    dp->scale = 1;
    dp->animate = animate_;

    emit signalDraw(dp, this, LAYER_DEFAULT);
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

} // end namespace td

