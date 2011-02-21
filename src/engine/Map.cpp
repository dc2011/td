#include "Map.h"

Map::Map(int heightInTiles, int widthInTiles)
{
    heightInTiles_ = heightInTiles;
    widthInTiles_ = widthInTiles;
/*
    tiles_ = new Tile**[heightInTiles_];
    for (int i = 0; i < heightInTiles_; i++)
    {
        tiles_[i] = new Tile*[widthInTiles_];
        for (int j = 0; j < widthInTiles_; j++)
        {
            tiles_[i][j] = new Tile;
        }
    }
    */
}

/**
  * This is a testing function pending a real map load function.
  *
  * This function will fill the tiles array and create fully blocked tiles
  * around the edges of the map. This can be used for collision detection.
  *
  * @author Luke Queenan
  */
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

/**
  * Slot for getting a tile's list of occupying units and blocking status
  *
  * For now, this function will only change the blocking type.
  *
  * @author Luke Queenan
  */
void Map::getTileInfo(int column, int row, int *blockingType)
{
    *blockingType = CLOSED;
}
