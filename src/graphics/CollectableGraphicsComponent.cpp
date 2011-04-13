#include "CollectableGraphicsComponent.h"
#include "../engine/Collectable.h"

#include <QPointF>
namespace td {

CollectableGraphicsComponent::~CollectableGraphicsComponent() {}

void CollectableGraphicsComponent::update(GameObject* obj) {
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
            dp->pos.setX(OFFSCREEN);
            dp->pos.setY(OFFSCREEN);
        } else {
            dp->pos = collectable->getPos();
        }

    } else {
        dp->pos = collectable->getPos();
    }

    dp->moving  = true;
    dp->scale   = collectable->getScale();
    dp->degrees = collectable->getOrientation();
    emit signalDraw(dp, this, LAYER_DEFAULT);
}

} /* end namespace td */

