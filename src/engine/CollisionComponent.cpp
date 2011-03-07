#include "CollisionComponent.h"

namespace td {

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
	
	double posXWhole;
	double posXFract;
	double posYWhole;
	double posYFract;
	
	
	posXWhole = modf(pos.x(), &posXFract);
	posYWhole = modf(pos.y(), &posYFract);
	
	switch(type){
		case NORTH_WEST:
			if( posYFract < (1.0 - posXFract) ){
				return false;
			}
			break;
		case NORTH_EAST:
			if( (posXFract > posYFract) ){
				return false;
			}
			break;
		case SOUTH_WEST:
			if( (posXFract < posYFract) ){
				return false;
			}
			break;
		case SOUTH_EAST:
			if( posYFract > (1.0 - posXFract) ){
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

} /* end namespace td */
