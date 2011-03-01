#ifndef MAP_H
#define MAP_H

#include "../util/mutex_magic.h"
#include <QObject>
#include <QMutex>
#include <math.h>
#include "Tile.h"
namespace td{

    class Map : public QObject {
        Q_OBJECT


        THREAD_SAFE_SINGLETON

    private:
                /**
             * The static singleton instance of the NetworkClient.
             *
             * It should only be retrieved using the instance() method, which
             * will initialize it the first time that it is retrieved.
             */
                static Map* instance_;





    private:

        explicit Map(int heightInTiles, int widthInTiles);

        virtual ~Map() { }






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
         * Create and initialize the NetworkClient instance.
         * This must be the first NetworkClient function that is called. Once an
         * instance has been created, all calls to init() or instance() will
         * return the existing instance.
         *
         * @author Ian Lee
         * @param heightInTiles number of tiles map is high
         * @param widthInTiles number of tiles map is wide
         * @return A pointer to the initialized Map instance.
         */
        static Map* init(int heightInTiles,int widthInTiles);
        /**
         * not implemented yet
         * This should only be called once, when the program is exiting.
         *
         * @author Ian Lee
         */
        static void shutdown();

        /**
         * Return the instance of the Map.
         * You MUST call init() to create the initial instance. Once an instance
         * has been created, all calls to init() or instance() will return the
         * existing instance.
         *
         * @author Ian Lee
         * @return A pointer to the Map instance.
         */
        static Map* instance(){
            return instance_;
        }

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
      *  basic map creator function
      *
      * @author Ian Lee
      */
        void loadTestMap2();

        /**

      * gets the row and column from coords x,y
      * stores in pointers row and column
      *
      *@author Ian Lee
      */
        void getTileCoords(double x, double y, int* row, int* column);
        /**

      * gets the Tile from coords x,y
      *
      *
      *@author Ian Lee
      */
        Tile* getTile(double x, double y);

        /**

      * gets the Units from Tiles surounding coords x,y in radius
      * currently radius is an int -> number of tiles away
      *
      *@author Ian Lee
      */
        std::set<Unit*> getUnits(double x, double y, double radius);


    };

}

#endif
