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
    void getTileInfo(int column, int row, int *blockingType);

public:
    static Map* init(int heightInTiles,int widthInTiles);
    static void shutdown();
    static Map* instance(){
        return instance_;
    }


    void loadTestMap();
    void loadTestMap2();
    void getTileCoords(double x, double y, int* row, int* column);
    Tile* getTile(double x, double y);
    std::set<Unit*> getUnits(double x, double y, double radius);


};

}

#endif
