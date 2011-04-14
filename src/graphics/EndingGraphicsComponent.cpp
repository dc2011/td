
#include "EndingGraphicsComponent.h"

namespace td {

QPixmap* EndingGraphicsComponent::pixmapImgs_ = 0;

void EndingGraphicsComponent::update(GameObject*) {
    DrawParams* dp = new DrawParams();

    emit signalDraw(dp, this, LAYER_DEFAULT);
}

void EndingGraphicsComponent::draw(DrawParams *dp, int layer) {
    GraphicsComponent::draw(dp, layer);
}

void EndingGraphicsComponent::animate() {
    if (!(animateCount_++ % animateMod_)) {
        ++pixmapIndex_ > arrayIndexMax_ ? pixmapIndex_ = arrayIndexMin_
            : pixmapIndex_;
        setImgIndex(pixmapIndex_);
    }
}

}
