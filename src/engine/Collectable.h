#ifndef TD_COLLECTABLE_H
#define TD_COLLECTABLE_H

#include "Unit.h"

namespace td {

/**
 * A collectable is any item that can be dropped by a unit, and later picked up.
 * This includes resources dropped by a player, and gems dropped by NPCs.
 * Collectables eventually disappear if they're not picked up.
 */
class Collectable : public Unit {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kCollectable;
    }

private:
    enum {
        kPosition       = (1 << 0),
        kOrientation    = (1 << 1),
        kScale          = (1 << 2),
        kType           = (1 << 3),
        kStartPos       = (1 << 4),
        kEndPos         = (1 << 5)
    };

public:
    Collectable(QObject* parent = 0);
    virtual ~Collectable();

    /**
     * Reads the object state from a network stream.
     * You should assign to variables directly inside this function, rather
     * than using mutator methods to change the values.
     *
     * @author Darryl Pogue
     * @param s The network stream.
     */
    virtual void networkRead(td::Stream* s);

    /**
     * Writes the object state to a network stream.
     *
     * @author Darryl Pogue
     * @param s The network stream.
     */
    virtual void networkWrite(td::Stream* s);

    /**
     * This function will do any component initialization whenever
     * a gameobject is created.
     *
     * @author Duncan Donaldson
     */
    virtual void initComponents();
    
    /**
     * Updates the resource every game tick.
     *
     * @author Dean Morin
     */
    virtual void update();

    /**
     * Sets path of the collectable for input.
     *
     * @param source The source point of the path.
     * @param vel The velocity of the unit that dropped the collectable.
     *
     * @author Dean Morin
     */
    void setPath(QPointF source, QVector2D vel);

    /**
     * Sets the collectable type (resource, gem).
     *
     * @author Dean Morin
     * @param type Collectable type.
     */
    void setType(int type) {
        type_ = type;
        setDirty(kType);
    }

    /**
     * Returns the original starting point of the collectable.
     *
     * @author Marcel Vangrootheest
     * @return The original starting position of the collectable.
     */
    QPointF* getStartPoint() {
        return start_;
    }

    /**
     * Sets the original starting point of the collectable.
     *
     * @author Marcel Vangrootheest
     * @param point The point to set the start location as.
     */
    void setStartPoint(QPointF* point) {
        start_ = point;
        setDirty(kStartPos);
    }

    /**
     * Returns the original ending point of the collectable.
     *
     * @author Marcel Vangrootheest
     * @return The original ending position of the collectable.
     */
    QPointF* getEndPoint() {
        return end_;
    }

    /**
     * Sets the ending point of the collectable.
     *
     * @author Marcel Vangrootheest
     * @param point The ending point set the end location as.
     */
    void setEndPoint(QPointF* point) {
        end_ = point;
        setDirty(kEndPos);
    }

    /**
     * Returns the line that makes up the current position and ending position.
     *
     * @author Marcel Vangrootheest
     * @return The current path of the collectable.
     */
    QLineF& getPath() {
        return path_;
    }

    /**
     * Sets the current path to the argument path.
     *
     * @author Marcel Vangrootheest
     * @param path The new path for the projectile.
     */
    void setPath(QLineF& path) {
       path_ = path;
    }

    /**
     * Returns the type of collectable (resource, gem).
     *
     * @author Dean Morin
     * @return The collectable type.
     */
    int getType() {
        return type_;
    }

    /**
     * Gets the width of the Collectable's bounding box.
     *
     * @author Dean Morin
     * @return Width The width of the bounding box.
     */
    int getWidth(){
        return width_;
    }

    /**
     * Sets the width of the Collectable's bounding box.
     *
     * @author Dean Morin
     * @param Width The width of the bounding box.
     */
    void setWidth(int width){
        width_ = width;
    }

    /**
     * Gets the height of the Collectable's bounding box.
     *
     * @author Dean Morin
     * @return Height The width of the bounding box.
     */
    int getHeight() {
        return height_;
    }

    /**
     * Sets the height of the Collectable's bounding box.
     *
     * @author Dean Morin
     * @param height The height of the bounding box.
     */
    void setHeight(int height) {
        height_ = height;
    }

    /**
     * Returns the number of ticks left before the collectable disappears.
     *
     * @author Dean Morin
     * @return The remaining count before it disappears.
     */
    int getDisappearCount() {
        return disappearCount_;
    }

signals:
    /**
     * Deletes the collectable.
     *
     * Connected to deleteObjLocal() in CDriver.
     *
     * @author Dean Morin
     */
    void deleteCollectableLater(int id);
    
private:
    /** The type of collectable (resource or gem). */
    int type_;

    /** The height of the bounding box. */
    int height_;
    
    /** The width of the bounding box. */
    int width_;

    /** Initial start position of the projectile. This needs to be initialized 
     *  before physics component is set. */
    QPointF* start_;

    /** Initial end position of the projectile. This needs to be initialized 
     *  before physics component is set. */
    QPointF* end_;

    /** Current path of the collectable. The first position is the end, and the
     *  second is the start of the path. */
    QLineF path_;

    /** The number of game ticks before the collectable disappears, if not
     *  picked up. */
    int disappearCount_;
};

} // end namespace td

#endif

