#include "CollisionComponent.h"

bool CollisionComponent::update(QPointF pos)
{
    if (parent_ == NULL)
    {
        return false;
    }

    int blockingType = 0;

    QPointF currentPosition = parent_->getPos();
    int y = floor(currentPosition.y() / TILE_HEIGHT);
    int x = floor(currentPosition.x() / TILE_WIDTH);

    emit requestTileInfo(x, y, &blockingType);

    if (blockingType == OPEN)
    {
        return true;
    }
    else if (blockingType == CLOSED)
    {
    	return false;
    }
    else
    {
        // TODO: This is where we will call a function to determine what areas
        // are blocked due to other blocking types or other units
        if(semiBlocked(pos, blockingType)){
        	return true;
        }
        return false;
    }
}

bool CollisionComponent::semiBlocked(QPointF pos, int type){
	switch(type){
		case NORTH_WEST:
			if( (10 - ((int)pos.x() % 10)) < (int)pos.y() ){
				return false;
			}
			break;
		case NORTH_EAST:
			if( ((int)pos.x() % 10) > ((int)pos.y() % 10) ){
				return false;
			}
			break;
		case SOUTH_WEST:
			if( ((int)pos.x() % 10) < ((int)pos.y() % 10) ){
				return false;
			}
			break;
		case SOUTH_EAST:
			if( (10 - ((int)pos.x() % 10)) < (int)pos.y() ){
				return false;
			}
			break;
		default:
			break;
	}
	return true;
}

void CollisionComponent::setParent(Unit *parent)
{
    parent_ = parent;
}

