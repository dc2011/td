#ifndef TD_TILE_H
#define TD_TILE_H

// System includes
#include <QObject>
#include <QSet>
#include <QPointF>
#include <QPolygon>
#include <QVector>

#include "../util/defines.h"
#include "ClsIdx.h"

namespace Tiled {
class Tile;
}

namespace td {

class TileExtension;
class Unit;

class Tile : public QObject {
    Q_OBJECT
public:
    enum BlockingType {
        OPEN,
        CLOSED,
        NORTH_WEST,
        NORTH_EAST,
        SOUTH_WEST,
        SOUTH_EAST,
    };

    enum TileEffect {
        NONE,
        SLOW,
        FAST,
    };

    struct TileAttributes {
        BlockingType type;
        TileEffect effect;
    };

    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() { return clsidx::kTile; }

    Tile();
    Tile(int row, int column, BlockingType type, TileEffect tileEffect);
    virtual ~Tile() { }

    // The following two methods are going to be problematic in their current
    // implementation as they rely on hard-coded MAP_ROWS and MAP_COLUMNS 
    // values. They also are not being used yet, so I have commented them out.
    // -- Love, Tom :)
    //int getColumn();
    //int getRow();
    void addUnit(Unit *unitToAdd);
    void removeUnit(Unit *unitToRemove);
    QList<Unit*> getUnits();
    BlockingType getType();

    /**
     * Returns the effect associated with this tile, or NULL if there is no
     * effect.
     *
     * @return the effect associated with this tile.
     * @author Luke Queenan
     */
    TileEffect getTileEffect()
    {
        return tileEffect_;
    }

    /**
     * setter for tile effect.
     *
     * @param tileEffect, the effect to set to the tile.
     * @author DTRAIN
     */
    void getTileEffect(TileEffect tileEffect)
    {
        tileEffect_ = tileEffect;
    }

    /**
     * Specifies whether a tile is one of the following:
     * Regular, buildable, built tower, resource, base
     *
     * @author Marcel Vangrootheest
     * returns the tile's action type
     */
    int getActionType() {
        return actionType_;
    }

    /**
     * Sets the action type for the tile.
     *
     * @author Marcel Vangrootheest
     * @param type the new action type for the tile
     */
    void setActionType(int type) {
        actionType_ = type;
    }
    
    /**
     * Gets the coordinates at the centre of the tile.
     *
     * @author Dean Morin
     * @return The coordinates of the centre of the tile.
     */
    QPointF& getPos() {
        return pos_;
    }

    /**
      * Gets the tile's bounding area.
      *
      * @author Luke Queenan
      * @return A polygon representing the blocked area of the tile.
      */
    QPolygonF getBounds()
    {
        return myBounds_;
    }

    /**
      * Sets the tile's bounding area.
      *
      * @author Luke Queenan
      * @return void
      */
    void setBounds(QPolygonF bounds)
    {
        myBounds_ = bounds;
    }

    /**
      * Sets the tile's bounding area to blocked.
      *
      * This function will set a tile's bounding area to blocked status.
      *
      * @author Luke Queenan
      * @return void
      */
    void setBlocked();

    /**
     * Gets this tile's extension object.
     *
     * @author Tom Nightingale 
     * @return The tile extension.
     */
    TileExtension * getExtension() { return extension_; }

    /**
     * Set a tile extension on this tile.
     *
     * @param extension The extension to set on the tile.
     * @author Tom Nightingale
     */
    void setExtension(TileExtension * extension) { extension_ = extension; }

    /**
     * Get the Tiled tile.
     * @return The Tiled tile.
     *
     * @author Tom Nightingale
     */
    Tiled::Tile * getTiledTile() { return tTile_; }

    /**
     * Set the Tiled tile used to create this TD tile.
     *
     * @param tile a pointer to the Tiled tile.
     * @author Tom Nightingale
     */
    void setTiledTile(Tiled::Tile * tile) { tTile_ = tile; }

    /**
     * Get a tile's tile attributes from its Tiled ID. The attributes are
     * stored in a static array within this method so that it is only loaded
     * once at runtime. As new tiles are added to the sprite, their attributes
     * will need to be added to this static array.
     *
     * @param id The id returned from the Tiled tile classes getId() method.
     * @return The tile's attributes.
     *
     * @author Tom Nightingale
     */
    static TileAttributes getAttributes(int id);

private:
    int tileID_;
    BlockingType type_;
    QList<Unit*> currentUnits_;
    QPolygonF myBounds_;
    int actionType_;
    TileEffect tileEffect_;
    Tiled::Tile * tTile_;

    /** 
     * Tiles can have an extension attached to them. Currently this is a tower 
     * or a resource. 
     */
    TileExtension * extension_;

    /**
     * The coordinates of the centre of the tile.
     */
    QPointF pos_;

    void setInitialBounds(int row, int column, BlockingType type);
};

} /* end namespace td */

#endif
