#include "CollectableGraphicsComponent.h"
#include "../engine/Collectable.h"

#include <QPointF>
namespace td {

CollectableGraphicsComponent::~CollectableGraphicsComponent() {}

void CollectableGraphicsComponent::update(GameObject* obj) {
    Collectable* collectable = (Collectable*)obj;

    if (!collectable->isDirty()) {
        return;
    }
    collectable->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = collectable->getPos();
    dp->moving  = true;
    dp->scale   = collectable->getScale();
    dp->degrees = collectable->getOrientation();
    emit signalDraw(dp, this, LAYER_DEFAULT);
}

} /* end namespace td */

