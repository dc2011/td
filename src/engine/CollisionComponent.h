#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include <QObject>
#include <QEvent>
#include <math.h>
#include "Tile.h"
#include "Unit.h"

// This is also located in Tile.h
//enum blockingType {OPEN = 0, CLOSED = 1, NORTH_WEST = 2, NORTH_EAST = 3,
//                   SOUTH_WEST = 4, SOUTH_EAST = 5};

class Unit;
class CollisionComponent : public QObject {
    Q_OBJECT
public:
    virtual ~CollisionComponent() {}

    /**
     * Classes need to define a method of setting their parent (owner) object.
     *
     * @author Tom Nightingale
     * @author Luke Queenan
     */
    void setParent(Unit*);

    /**
     * Will perform the collision tests and return true if the move is valid
     * or false if it is invalid.
     *
     * @author Luke Queenan
     */
    bool update(QPointF pos);
	/**
	* Return true if pos is in unblocked half of tile.
	* Return false if pos is in blocked half of tile.
	*
	* @author Daniel Wright
	*/
    bool semiBlocked(QPointF pos, int type);

signals:
    void requestTileInfo(int row, int col, int *blockingType);

private:
    Unit *parent_;
};

#endif
