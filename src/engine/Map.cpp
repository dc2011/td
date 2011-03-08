#include "Map.h"
#include "Tile.h"
#include "../graphics/MapDisplayer.h"
#include "../client/MainWindow.h"

/** Tiled headers. */
#include "isometricrenderer.h"
#include "map.h"
#include "mapobject.h"
#include "mapreader.h"
#include "objectgroup.h"
#include "orthogonalrenderer.h"
#include "tilelayer.h"
#include "tileset.h"
#include "tile.h"

namespace td{

    Map::Map(int heightInTiles, int widthInTiles)
    {
        heightInTiles_ = heightInTiles;
        widthInTiles_ = widthInTiles;
        waypoints = QMap<int,QList<QPoint> >();
    }

    void Map::initMap() {
        tiles_ = new Tile**[heightInTiles_];
        //QGraphicsItem * gTile = NULL;
        MapDisplayer * md = MainWindow::instance()->getMD();
        blockingType type;

        for (int row = 0; row < heightInTiles_; row++) {
            tiles_[row] = new Tile*[widthInTiles_];

            for (int col = 0; col < widthInTiles_; col++) {
                //gTile = md->itemAt(row, col);
                type = OPEN; //default type
                // area to add logic for tile creation
                if( row ==0 || col == 0 || row == heightInTiles_-1 || col == widthInTiles_ -1 ) {
                    type = CLOSED; //border of map gets CLOSED status
                }
                // end for logic
                //save into array
                tiles_[row][col] = new Tile(row, col, type);
            }
        }
    }

    void Map::loadTestMap2(){
        blockingType type;
        tiles_ = new Tile**[heightInTiles_];
        for (int i = 0; i < heightInTiles_; i++)
        {
            tiles_[i] = new Tile*[widthInTiles_];
            for (int j = 0; j < widthInTiles_; j++)
            {
                type = OPEN; //default type
                // area to add logic for tile creation
                if( i ==0 || j == 0 || i == heightInTiles_-1 || j == widthInTiles_ -1 ){
                    type = CLOSED; //border of map gets CLOSED status
                }
                // end for logic
                //save into array
                tiles_[i][j] = new Tile(i,j,type);
            }
        }
    }

    void Map::getTileType(double x, double y, int *blockingType)
    {
        int row = floor(y / TILE_HEIGHT);
        int col = floor(x / TILE_WIDTH);

        *blockingType = tiles_[row][col]->getType();
    }

    void Map::getTileCoords(double x, double y, int* row, int* column){
        *row = floor(y / TILE_HEIGHT);
        *column= floor(x / TILE_WIDTH);
    }

    Tile* Map::getTile(double x, double y){
        int r,c;
        getTileCoords(x,y,&r,&c);
        return tiles_[r][c];

    }

    QSet<Unit*> Map::getUnits(double x, double y, double radius){
        int i,j;
        int r,c;
        getTileCoords(x,y,&r,&c);

        QSet<Unit*> units = QSet<Unit*>();

        for (i = 0; i< radius ; i++){
            for(j=0; j+i < radius ; j++){
                if( i + r < heightInTiles_){

                    if(j + c < widthInTiles_){
                        units += tiles_[i+r][j+c]->getUnits();
                    } 
                    if(c - j >= 0){
                        units += tiles_[i+r][c-j]->getUnits();
                    }

                }
                if( r - i >= 0){

                    if(j + c < widthInTiles_){
                        units += tiles_[i+r][j+c]->getUnits();
                    }
                    if(c - j >= 0){
                        units += tiles_[r-i][c-j]->getUnits();
                    }
                }
            }
        }
        return units;
    }

}//end namespace 
