#include "Map.h"

namespace td{



    //Map* Map::instance_ = NULL;
    //QMutex Map::mutex_;

    Map::Map(int heightInTiles, int widthInTiles)
    {
        heightInTiles_ = heightInTiles;
        widthInTiles_ = widthInTiles;
        waypoints = QMap<int,QList<QPoint> >();



    }



    void Map::loadTestMap()
    {
        int count = 0;
        // Create top and bottom edges with blocking tiles
        /*
    for (count = 0; count < heightInTiles_; count++)
    {
        Tile *topRow = new Tile(0, count, CLOSED);
        tiles_[0][count] = topRow;
        // Subtract 1 for zero base...
        tiles_[heightInTiles_ - 1][count] =
                Tile(heightInTiles_ - 1, count, CLOSED);
    }
    */
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


    void Map::getTileInfo(int row, int column, int *blockingType)
    {
        //*blockingType = CLOSED;

        //should work @author ian
        *blockingType = tiles_[row][column]->getType();


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

    std::set<Unit*> Map::getUnits(double x, double y, double radius){
        int i,j;
        int r,c;
        getTileCoords(x,y,&r,&c);
        std::set<Unit*> tempUnits;
        std::set<Unit*> units = std::set<Unit*>();

        for (i = 0; i< radius ; i++){
            for(j=0; j+i < radius ; j++){
                if( i + r < heightInTiles_){

                    if(j + c < widthInTiles_){
                        tempUnits = tiles_[i+r][j+c]->getUnit();

                        std::set<Unit*>::iterator iter;
                        for( iter = tempUnits.begin();iter!= tempUnits.end();iter++){
                            units.insert(*iter);
                        }
                    }
                    if(c - j >= 0){
                        tempUnits = tiles_[i+r][c-j]->getUnit();

                        std::set<Unit*>::iterator iter;
                        for( iter = tempUnits.begin();iter!= tempUnits.end();iter++){
                            units.insert(*iter);
                        }
                    }

                }
                if( r - i >= 0){

                    if(j + c < widthInTiles_){
                        tempUnits = tiles_[i+r][j+c]->getUnit();

                        std::set<Unit*>::iterator iter;
                        for( iter = tempUnits.begin();iter!= tempUnits.end();iter++){
                            units.insert(*iter);
                        }
                    }
                    if(c - j >= 0){
                        tempUnits = tiles_[r-i][c-j]->getUnit();

                        std::set<Unit*>::iterator iter;
                        for( iter = tempUnits.begin();iter!= tempUnits.end();iter++){
                            units.insert(*iter);
                        }
                    }
                }


            }
        }
        return units;
    }


}//end namespace 
