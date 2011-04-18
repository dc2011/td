#include "CollectableGraphicsComponent.h"
#include <QPointF>
#include "../engine/Collectable.h"

namespace td {

CollectableGraphicsComponent::~CollectableGraphicsComponent() {}


void CollectableGraphicsComponent::update(GameObject* obj) {
    bool visible;

    Collectable* collectable = (Collectable*)obj;
    int timeLeft = collectable->getDisappearCount();

    if (timeLeft > FLICKER_POINT && !collectable->isDirty()) {
        return;
    }
    collectable->resetDirty();


    DrawParams* dp = new DrawParams();

    if (timeLeft <= FLICKER_POINT) {

        if (timeLeft % FLICKER_RATE == 0) {
            flickerShow_ = !flickerShow_;
        }
            
        if (!flickerShow_) {
            visible = false;
            dp->pos.setX(OFFSCREEN);
            dp->pos.setY(OFFSCREEN);
        } else {
            visible = true;
            dp->pos = collectable->getPos();
        }

    } else {
        visible = true;
        dp->pos = collectable->getPos();
    }
    if (oldstate_ != visible || oldPos_ != dp->pos) {
        oldstate_ = visible;
        oldPos_ = dp->pos;
        dp->scale   = collectable->getScale();
        dp->degrees = collectable->getOrientation();
        dp->animate = animate_;
        emit signalDraw(dp, this, LAYER_DEFAULT);
    } else {
        delete dp;
    }
}

} /* end namespace td */

