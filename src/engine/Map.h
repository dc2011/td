#ifndef MAP_H
#define MAP_H

#include "../util/mutex_magic.h"
#include <QObject>
#include <QPoint>
#include <QList>
#include <QMap>
#include <QMutex>
#include <math.h>
#include "Tile.h"
namespace td{

    class Map : public QObject {
        Q_OBJECT





    public:

        explicit Map(int heightInTiles, int widthInTiles);

        virtual ~Map() { }


    private:

        QMap<int,QList<QPoint> > waypoints;

        Tile ***tiles_;
        int heightInTiles_;
        int widthInTiles_;

    public slots:
        /**
      * Slot for getting a tile's list of occupying units and blocking status
      *
      * For now, this function will only change the blocking type.
      *
      * @author Luke Queenan
      */
        void getTileInfo(int column, int row, int *blockingType);

    public:



        /**
      * This is a testing function pending a real map load function.
      *
      * This function will fill the tiles array and create fully blocked tiles
      * around the edges of the map. This can be used for collision detection.
      *
      * @author Luke Queenan
      */
        void loadTestMap();
        /**
      *  basic map creator function.
      *
      * @author Ian Lee
      */
        void loadTestMap2();

        /**

      * gets the row and column from coords x,y.
      * stores in pointers row and column
      *
      *@author Ian Lee
      */
        void getTileCoords(double x, double y, int* row, int* column);
        /**

      * gets the Tile from coords x,y.
      *
      *
      *@author Ian Lee
      */
        Tile* getTile(double x, double y);

        /**

      * gets the Units from Tiles surounding coords x,y in radius.
      * currently radius is an int -> number of tiles away
      *
      *@author Ian Lee
      */
        std::set<Unit*> getUnits(double x, double y, double radius);

        /**
          * gets all waypoints stored.
          *
          * @author Ian Lee
          */
        QMap<int,QList<QPoint> > getAllWaypoints(){
            return waypoints;
        }

        /**
          * gets waypoints associated with key
          *
          *@author Ian Lee
          */
        QList<QPoint> getWaypoints(int key){
            return waypoints[key];
        }
        /**
          * inserts waypoint list to qmap
          *
          *@author Ian Lee
          */
        void addWaypoints(int key ,QList<QPoint> newSet){
            waypoints.insert(key, newSet);
        }

    };

}

#endif
