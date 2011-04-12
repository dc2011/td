#ifndef TD_COLLECTABLE_H
#define TD_COLLECTABLE_H

#include "Unit.h"

namespace td {

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
     * Returns the original starting point of the projectile.
     *
     * @author Marcel Vangrootheest
     * @return the original starting position of the projectile
     */
    QPointF* getStartPoint() {
        return start_;
    }

    /**
     * Sets the original starting point of the projectile.
     *
     * @author Marcel Vangrootheest
     * @param point, the point to set the start location as
     */
    void setStartPoint(QPointF* point) {
        start_ = point;
        setDirty(kStartPos);
    }

    /**
     * Returns the original ending point of the projectile.
     *
     * @author Marcel Vangrootheest
     * @return the original ending position of the projectile
     */
    QPointF* getEndPoint() {
        return end_;
    }

    /**
     * Sets the ending point of the projectile.
     *
     * @author Marcel Vangrootheest
     * @param point, the ending point set the end location as
     */
    void setEndPoint(QPointF* point) {
        end_ = point;
        setDirty(kEndPos);
    }

    /**
     * Returns the line that makes up the current position and ending position
     *
     * @author Marcel Vangrootheest
     * @return the current path of the projectile
     */
    QLineF& getPath() {
        return path_;
    }

    /**
     * Sets the current path to path.
     *
     * @author Marcel Vangrootheest
     * @param path, the new path for the projectile
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

    int getWidth(){
        return width_;
    }

    void setWidth(int width){
        width_ = width;
    }

    int getHeight(){
        return height_;
    }

    void setHeight(int height){
        height_ = height;
    }
    
protected:
    /** Input handling logic for this Unit is contained in this component. */
    InputComponent* input_;

private:
    /** The type of collectable (resource or gem). */
    int type_;
    int height_;
    int width_;
    /**
     * Initial start position of the projectile.
     * This needs to be initialized before physics component is set.
     */
    QPointF* start_;
    /**
     * Initial end position of the projectile.
     * This needs to be initialized before physics component is set.
     */
    QPointF* end_;
    /**
     * Current path of the projectile. Second position should be set to start
     * or the current projectile position. First position should be set to end.
     */
    QLineF path_;
};

} // end namespace td

#endif

