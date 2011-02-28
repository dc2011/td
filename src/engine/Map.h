#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <math.h>
#include "Tile.h"

class Map : public QObject {
    Q_OBJECT

public:
    Map(int heightInTiles, int widthInTiles);
    virtual ~Map() { }

    void loadTestMap();
    void getTileCoords(double x, double y, int* row, int* column);
    void loadTestMap2();

private:
    Tile ***tiles_;
    int heightInTiles_;
    int widthInTiles_;

public slots:
    void getTileInfo(int column, int row, int *blockingType);

};

#endif
