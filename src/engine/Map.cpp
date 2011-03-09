#include "Map.h"
#include "Tile.h"
#include "../graphics/MapDisplayer.h"
#include "../client/MainWindow.h"

/** Tiled headers. */
// TODO: I am pretty sure we only *actually* need to include map.h and tile.h
//       here.
#include <isometricrenderer.h>
#include <map.h>
#include <mapobject.h>
#include <mapreader.h>
#include <objectgroup.h>
#include <orthogonalrenderer.h>
#include <tilelayer.h>
#include <tileset.h>
#include <tile.h>

namespace td{

    Map::Map(Tiled::Map * tMap) {
        tMap_ = tMap;
        waypoints = QMap<int,QList<QPointF> >();
    }

    void Map::initMap() {
        blockingType type;
        Tiled::Tile * tile = NULL;
        Tiled::TileLayer * tileLayer = tMap_->layerAt(0)->asTileLayer();
        Tiled::TileLayer * towerLayer = tMap_->layerAt(1)->asTileLayer();
        //Tiled::TileLayer * resLayer = tMap_->layerAt(2)->asTileLayer();
        Tiled::ObjectGroup * path = tMap_->layerAt(3)->asObjectGroup();
        heightInTiles_ = tileLayer->height();
        widthInTiles_ = tileLayer->width();

        tiles_ = new Tile**[heightInTiles_];

        for (size_t row = 0; row < heightInTiles_; row++) {
            tiles_[row] = new Tile*[widthInTiles_];

            for (size_t col = 0; col < widthInTiles_; col++) {
                tile = tileLayer->tileAt(col, row);
                type = (blockingType) tile->id(); //default type
                //save into array
                tiles_[row][col] = new Tile(row, col, type);
                if (towerLayer->contains(col, row)
                        && towerLayer->tileAt(col, row) != NULL) {
                    tiles_[row][col]->setActionType(TILE_BUILDABLE);
                    //qDebug("TowerTile at: %d, %d", col, row);
                }
            }
        }
        makeWaypoints(WP_PTERO, path);

    }

    void Map::makeWaypoints(int key, Tiled::ObjectGroup* path) {
        int i = 0;
        QList<QPointF>* newPath = new QList<QPointF>();
        QColor c = QColor();

        //Doesn't actually make it green. But still useful.
        path->setColor(c.green());
        for (i = 0; i < path->objects().size(); i++) {
            newPath->push_back(QPointF(path->objects().at(i)->position().x()*48,
                        path->objects().at(i)->position().y() * 48));
        }
        addWaypoints(key, newPath);
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

    Tile* Map::getTile(QPointF coords) {
        return Map::getTile(coords.x(), coords.y());
    }

    QSet<Tile*> Map::getTiles(QPointF coords, int radius){

        int i,j,r,c;
        QSet<Tile*> tempTiles = QSet<Tile*>();
        getTileCoords(coords.x(),coords.y(),&r,&c);

        for (i = 0; i< radius ; i++){
            for(j=0; j+i < radius ; j++){
                if( i + r < heightInTiles_){

                    if(j + c < widthInTiles_){
                        tempTiles += tiles_[i+r][j+c];
                    }
                    if(c - j >= 0){
                        tempTiles += tiles_[i+r][c-j];
                    }

                }
                if( r - i >= 0){

                    if(j + c < widthInTiles_){
                        tempTiles += tiles_[i+r][j+c];
                    }
                    if(c - j >= 0){
                        tempTiles += tiles_[r-i][c-j];
                    }
                }
            }
        }
        return tempTiles;
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

    void Map::addUnit(double x, double y, Unit *unitToAdd)
    {
        int row = 0;
        int column = 0;

        getTileCoords(x, y, &row, &column);

        tiles_[row][column]->addUnit(unitToAdd);
        //qDebug("add to tile: %d, %d",row, column);
    }

    void Map::removeUnit(double x, double y, Unit *unitToRemove)
    {
        int row = 0;
        int column = 0;

        getTileCoords(x, y, &row, &column);

        tiles_[row][column]->removeUnit(unitToRemove);
        //qDebug("leaving tile: %d, %d", row, column);
    }

}//end namespace 
