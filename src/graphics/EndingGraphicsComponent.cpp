
#include "EndingGraphicsComponent.h"

namespace td {

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
