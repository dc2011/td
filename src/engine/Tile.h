#ifndef TD_TILE_H
#define TD_TILE_H

// System includes
#include <QObject>
#include <set>
#include <QSet>
#include <QPointF>

#include "ClsIdx.h"

//temp defines
#define TILE_HEIGHT 48
#define TILE_WIDTH 48

namespace td {

// May need a better place for this definition since it is needed in collision
enum blockingType {OPEN = 0, CLOSED = 1, NORTH_WEST = 2, NORTH_EAST = 3,
                   SOUTH_WEST = 4, SOUTH_EAST = 5};

class Unit;

class Tile : public QObject {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() { return clsidx::kTile; }

public:
    Tile();
    Tile(int row, int column, blockingType type);
    virtual ~Tile() { }

    int getColumn();
    int getRow();
    void addUnit(Unit *unitToAdd);
    void removeUnit(Unit *unitToRemove);
    QSet<Unit*> getUnits();
    blockingType getType();
    
    /**
     * Gets the coordinates at the centre of the tile.
     *
     * @author Dean Morin
     * @return The coordinates of the centre of the tile.
     */
    QPointF& getPos() {
        return pos_;
    }

private:
    int tileID_;
    blockingType type_;
    QSet<Unit*> currentUnits_;


    /**
     * The coordinates of the centre of the tile.
     */
    QPointF pos_;

};

} /* end namespace td */

#endif
