#ifndef TD_MAP_H
#define TD_MAP_H

#include "../util/mutex_magic.h"
#include "../util/defines.h"
#include <QObject>
#include <QPoint>
#include <QList>
#include <QSet>
#include <QMap>
#include <QMutex>
#include <math.h>

namespace Tiled {
class ObjectGroup;
class Map;
}

namespace td {

class Unit;
class Tile;
class Resource;

class Map : public QObject {
    Q_OBJECT

public:
    explicit Map(Tiled::Map * tMap);
    virtual ~Map() { }

private:
    /**  */
    QMap<int,QList<QPointF> > waypoints;

    /**  */
    Tile ***tiles_;

    /**  */
    Tiled::Map * tMap_;

    /**  */
    int heightInTiles_;

    /**  */
    int widthInTiles_;

    /**
     * Creates a resource to be placed on a tile.
     *
     * @param type The type of resource to create.
     * @param tile The tile to add the new resource to.
     */
    void createResource(int type, Tile * tile);

public:
    /**
     * This is a testing function pending a real map load function.
     *
     * This function will fill the tiles array and create fully blocked tiles
     * around the edges of the map. This can be used for collision detection.
     *
     * @author Luke Queenan
     */
    void initMap();

    /**
     * basic map creator function.
     *
     * @author Ian Lee
     */
    void loadTestMap2();

    /**
     * gets the row and column from coords x,y.
     * stores in pointers row and column
     *
     * @param x x coord of point
     * @param y y coord of point
     * @param r returned row of point
     * @param c returned column of point
     *
     * @author Ian Lee
     */
    void getTileCoords(double x, double y, int* row, int* column);

    /**
     * gets the Tile from coords x,y.
     *
     * @param x x coord of point
     * @param y y coord of point
     * @return pointer to tile containing coord x,y
     *
     * @author Ian Lee
     */
    Tile* getTile(double x, double y);
    
    /**
     * Gets the tile at the coordinates coords.
     *
     * @author Dean Morin
     * @param coords The coordinates to find the tile with.
     * @return pointer to tile containing coord
     *
     */
    Tile* getTile(QPointF coords);
    /**
     * Gets the Tiles surounding coordinates coords in radius.
     * @param coords The coordinates to find the tile with.
     * @param radius The radius around designated tile.
     * @return pointers to tiles around point coords
     * @author Ian Lee
     */
    QSet<Tile*> getTiles(QPointF coords, int radius);

    /**
     * gets the Units from Tiles surounding coords x,y in radius.
     * currently radius is an int -> number of tiles away
     *
     * @param x x coordinate of point.
     * @param y y coordinate of point.
     * @param radius radius around designated tile.
     * @return pointers to units contained by surrounding tiles of point.
     * @author Ian Lee
     */
    QSet<Unit*> getUnits(double x, double y, double radius);

    /**
      * gets all waypoints stored.
      *
      * @author Ian Lee
      * @return map of list of waypoints.
      */
    QMap<int,QList<QPointF> > getAllWaypoints(){
        return waypoints;
    }

    /**
     * gets waypoints associated with key
     *
     * @author Ian Lee
     * @param key key to get list of waypoints.
     * @return single series of waypoints.
     */
    QList<QPointF> getWaypoints(int key){
        return waypoints[key];
    }

    /**
     * inserts waypoint list to qmap
     * @param key key for new series of waypoints to be added.
     * @param newSet new series of waypoints to be added.
     * @author Ian Lee
     */
    void addWaypoints(int key ,QList<QPointF>* newSet){
        waypoints.insert(key, *newSet);
    }

    /**
     * Makes a list of waypoints based on QPointF and adds it to the Map.
     *
     * @author Marcel Vangrootheest
     * @param key to identify enemy type
     * @param path the object layer from tiled
     */
    void makeWaypoints(int key, Tiled::ObjectGroup* path);

    /**
      * Adds a pointer to a unit to the specified tile.
      *
      * @author Luke Queenan
      * @param x x coordinate for point.
      * @param y y coordinate for point.
      * @param unitToAdd pointer to unit to be added to tile's list.
      */
    void addUnit(double x, double y, Unit *unitToAdd);

    /**
      * Removes the unit from the specified tile.
      *
      * @author Luke Queenan
      * @param x x coordinate for point.
      * @param y y coordinate for point.
      * @param unitToRemove pointer to unit to be removed from tile's list.
      */
    void removeUnit(double x, double y, Unit *unitToRemove);

public slots:
    /**
     * Slot for getting a tile's list of occupying units and blocking status
     *
     * For now, this function will only change the blocking type.
     *
     * @author Luke Queenan
     * @param column location of tile.
     * @param row location of tile
     * @param blockingType tile's type.
     */
    void getTileType(double column, double row, int *blockingType);
};

}

#endif
