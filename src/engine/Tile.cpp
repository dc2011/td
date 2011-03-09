#include "Tile.h"
#include "Unit.h"
#include "TileExtension.h"

namespace td {

/**
  * The constructor for the tile class
  *
  * The tile class contains a tile's blocking property, its position in
  * the tile array (located in the map), and a set of units currently on
  * the tile.
  *
  * @author Luke Queenan
  *
  */
Tile::Tile(int row, int column, blockingType type)
{
    tileID_ = column * MAP_ROWS + row;
    type_ = type;
    setInitialBounds(row, column, type);
    actionType_ = TILE_REGULAR;
    int xPos = column * TILE_WIDTH + TILE_WIDTH / 2;
    int yPos = row * TILE_HEIGHT + TILE_HEIGHT / 2;
    pos_ = QPointF(xPos, yPos);
}

/**
  * Sets the bounding area for a tile.
  *
  * The logic for taking a blocking type and converting it to a bounding area.
  * Closed type will use a box based on the size of the tile, semiclosed tiles
  * will have a triangle. Open type will not have a bounding box. The
  * coordinates will be based on the position of the tile in the map.
  *
  * @author Luke Queenan
  */
void Tile::setInitialBounds(int row, int column, blockingType type)
{
    switch (type)
    {
    case CLOSED:

        myBounds_ = QPolygonF(12);

    }
}

/**
  * Returns the tile's column position in the array
  *
  * @author Luke Queenan
  * @return The tile's column position in the array
  */
int Tile::getColumn()
{
    return tileID_ / MAP_ROWS;
}

/**
  * Returns the tile's row position in the array
  *
  * @author Luke Queenan
  * @return The tile's row position in the array
  */
int Tile::getRow()
{
    return tileID_ % MAP_COLS;
}

/**
  * Returns the tile's blocking type
  *
  * @author Luke Queenan
  * @return The tile's blocking type
  */
blockingType Tile::getType()
{
    return type_;
}

/**
  * Adds a pointer to a unit to this tile's list of units.
  *
  * @author Luke Queenan
  * @return void
  */
void Tile::addUnit(Unit *unitToAdd)
{
    currentUnits_.insert(unitToAdd);
}

/**
  * Removes a pointer to a unit from this tile's list of units.
  *
  * @author Luke Queenan
  * @return void
  */
void Tile::removeUnit(Unit *unitToRemove)
{
    currentUnits_.remove(unitToRemove);
}

QSet<Unit*> Tile::getUnits(){
    return currentUnits_;

}

} /* end namespace td */

