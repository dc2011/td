#include "Tile.h"
#include "Unit.h"

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
Tile::Tile(int row, int column, BlockingType type, TileEffect tileEffect)
{
    tileID_ = column * MAP_ROWS + row;
    type_ = type;
    setInitialBounds(row, column, type);
    actionType_ = TILE_REGULAR;
    int xPos = column * TILE_WIDTH + TILE_WIDTH / 2;
    int yPos = row * TILE_HEIGHT + TILE_HEIGHT / 2;
    pos_ = QPointF(xPos, yPos);
    tileEffect_ = tileEffect;
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
void Tile::setInitialBounds(int row, int column, BlockingType type)
{
    QPointF point = QPointF();
    QVector<QPointF> points = QVector<QPointF>();
    switch (type) {
    case CLOSED:
        // Top left corner
        point.setX(column * TILE_WIDTH);
        point.setY(row * TILE_HEIGHT);
        points.append(point);
        // Top right corner
        point.setX(column * TILE_WIDTH + TILE_WIDTH);
        point.setY(row * TILE_HEIGHT);
        points.append(point);

        // Bottom right corner
        point.setX(column * TILE_WIDTH + TILE_WIDTH);
        point.setY(row * TILE_HEIGHT + TILE_HEIGHT);
        points.append(point);
        // Bottom left corner
        point.setX(column * TILE_WIDTH);
        point.setY(row * TILE_HEIGHT + TILE_HEIGHT);
        points.append(point);
        // Create bounding box
        myBounds_ = QPolygonF(points);
        break;

    case NORTH_WEST:
        // Top right corner
        point.setX(column * TILE_WIDTH + TILE_WIDTH);
        point.setY(row * TILE_HEIGHT);
        points.append(point);
        // Bottom left corner
        point.setX(column * TILE_WIDTH);
        point.setY(row * TILE_HEIGHT + TILE_HEIGHT);
        points.append(point);
        // Bottom right corner
        point.setX(column * TILE_WIDTH + TILE_WIDTH);
        point.setY(row * TILE_HEIGHT + TILE_HEIGHT);
        points.append(point);
        // Create bounding box
        myBounds_ = QPolygonF(points);
        break;

    case NORTH_EAST:
        // Top left corner
        point.setX(column * TILE_WIDTH);
        point.setY(row * TILE_HEIGHT);
        points.append(point);
        // Bottom left corner
        point.setX(column * TILE_WIDTH);
        point.setY(row * TILE_HEIGHT + TILE_HEIGHT);
        points.append(point);
        // Bottom right corner
        point.setX(column * TILE_WIDTH + TILE_WIDTH);
        point.setY(row * TILE_HEIGHT + TILE_HEIGHT);
        points.append(point);
        // Create bounding box
        myBounds_ = QPolygonF(points);
        break;

    case SOUTH_WEST:
        // Top left corner
        point.setX(column * TILE_WIDTH);
        point.setY(row * TILE_HEIGHT);
        points.append(point);
        // Top right corner
        point.setX(column * TILE_WIDTH + TILE_WIDTH);
        point.setY(row * TILE_HEIGHT);
        points.append(point);
        // Bottom right corner
        point.setX(column * TILE_WIDTH + TILE_WIDTH);
        point.setY(row * TILE_HEIGHT + TILE_HEIGHT);
        points.append(point);
        // Create bounding box
        myBounds_ = QPolygonF(points);
        break;

    case SOUTH_EAST:
        // Top left corner
        point.setX(column * TILE_WIDTH);
        point.setY(row * TILE_HEIGHT);
        points.append(point);
        // Top right corner
        point.setX(column * TILE_WIDTH + TILE_WIDTH);
        point.setY(row * TILE_HEIGHT);
        points.append(point);
        // Bottom left corner
        point.setX(column * TILE_WIDTH);
        point.setY(row * TILE_HEIGHT + TILE_HEIGHT);
        points.append(point);
        // Create bounding box
        myBounds_ = QPolygonF(points);
        break;

    default:
        break;
    }
}

/**
 * PLEASE SEE HEADER FILE FOR WHY THIS HAS BEEN COMMENTED.
 *
 * Returns the tile's column position in the array
 *
 * @author Luke Queenan
 * @return The tile's column position in the array
 */
//int Tile::getColumn()
//{
//    return tileID_ / MAP_ROWS;
//}

/**
 * PLEASE SEE HEADER FILE FOR WHY THIS HAS BEEN COMMENTED.
 *
 * Returns the tile's row position in the array
 *
 * @author Luke Queenan
 * @return The tile's row position in the array
 */
//int Tile::getRow()
//{
//    return tileID_ % MAP_COLS;
//}

/**
  * Returns the tile's blocking type
  *
  * @author Luke Queenan
  * @return The tile's blocking type
  */
Tile::BlockingType Tile::getType()
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

void Tile::setBlocked()
{
/*
    QPointF point = QPointF();
    QVector<QPointF> points = QVector<QPointF>();

    // Top left corner
    point.setX(column * TILE_WIDTH);
    point.setY(row * TILE_HEIGHT);
    points.append(point);
    // Top right corner
    point.setX(column * TILE_WIDTH + TILE_WIDTH);
    point.setY(row * TILE_HEIGHT);
    points.append(point);

    // Bottom right corner
    point.setX(column * TILE_WIDTH + TILE_WIDTH);
    point.setY(row * TILE_HEIGHT + TILE_HEIGHT);
    points.append(point);
    // Bottom left corner
    point.setX(column * TILE_WIDTH);
    point.setY(row * TILE_HEIGHT + TILE_HEIGHT);
    points.append(point);
    // Create bounding box
    myBounds_ = QPolygonF(points);
    type_ = CLOSED;
    */
}

QSet<Unit*> Tile::getUnits(){
    return currentUnits_;
}

Tile::TileAttributes Tile::getAttributes(int id) {
    static const TileAttributes attributes[] = {
        // Row 1
        {OPEN, NONE},
        {CLOSED, NONE},
        {NORTH_WEST, NONE},
        {NORTH_EAST, NONE},
        {SOUTH_WEST, NONE},
        {SOUTH_EAST, NONE},
        {NORTH_WEST, SLOW},
        {NORTH_EAST, SLOW},
        {SOUTH_WEST, SLOW},
        {SOUTH_EAST, SLOW},
        {NORTH_WEST, FAST},
        {NORTH_EAST, FAST},
        {SOUTH_WEST, FAST},
        {SOUTH_EAST, FAST},

        // Row 2
        {OPEN, NONE},
        {OPEN, FAST},
        {OPEN, FAST},
        {OPEN, FAST},
        {OPEN, FAST},
        {OPEN, FAST},
        {OPEN, FAST},
        {OPEN, FAST},
        {OPEN, FAST},
        {OPEN, FAST},
        {SOUTH_EAST, FAST},
        {SOUTH_WEST, FAST},
        {NORTH_EAST, FAST},
        {NORTH_WEST, FAST},

        // Row 3
        {OPEN, NONE},
        {CLOSED, NONE},
        {NORTH_WEST, NONE},
        {NORTH_EAST, NONE},
        {SOUTH_WEST, NONE},
        {SOUTH_EAST, NONE},
        {NORTH_WEST, SLOW},
        {NORTH_EAST, SLOW},
        {SOUTH_WEST, SLOW},
        {SOUTH_EAST, SLOW},

        // Row 4
        {OPEN, NONE},
        {OPEN, SLOW},
        {OPEN, SLOW},
        {OPEN, SLOW},
        {OPEN, SLOW},
        {OPEN, SLOW},
    };

    return attributes[id];
}

} /* end namespace td */

