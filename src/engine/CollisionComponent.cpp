#include "CollisionComponent.h"

bool CollisionComponent::update()
{
    qDebug("Calling CollisionComponent");
    if (parent_ == NULL)
    {
        qDebug("No Parent for Collision Component");
        return false;
    }
    int blockingType = 0;

    QPointF currentPosition = parent_->getPos();
    requestTileInfo((int)currentPosition.x(), (int)currentPosition.y(),
                    &blockingType);

    if (blockingType == CLOSED)
    {
        return false;
    }
    else
    {
        // TODO: This is where we will call a function to determine what areas
        // are blocked due to other blocking types or other units
        return true;
    }
}

void CollisionComponent::setParent(Unit *parent)
{
    parent_ = parent;
}

