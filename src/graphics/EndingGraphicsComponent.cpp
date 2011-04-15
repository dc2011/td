
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

}
