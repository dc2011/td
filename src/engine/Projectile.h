#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QVector2D>
#include <QPointF>

#include "Unit.h"

class Projectile : public Unit {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kProjectile;
    }

public:
    Projectile();

    /**
     * Creates new projectile.
     *
     * @author Pan Khantidhara, Marcel Vangrootheest
     * @param physics Physics component.
     * @param graphic Graphics component.
     * @param start, where the projectile starts
     * @param end, where the projectile ends
     */
    Projectile(PhysicsComponent* physics, GraphicsComponent* graphics,
               QPointF* start, QPointF* end);

    virtual void update();

    size_t getDamage(){
        return damage_;
    }

    void setDamage(size_t damage){
        damage_ = damage;
    }

    /**
     * Returns the original starting point of the projectile.
     *
     * @author Marcel Vangrootheest
     * @return the original starting position of the projectile
     */
    QPointF* getStartPoint(){
        return start_;
    }

    /**
     * Sets the original starting point of the projectile.
     *
     * @author Marcel Vangrootheest
     * @param point, the point to set the start location as
     */
    void setStartPoint(QPointF* point){
        start_ = point;
    }

    /**
     * Returns the original ending point of the projectile.
     *
     * @author Marcel Vangrootheest
     * @return the original ending position of the projectile
     */
    QPointF* getEndPoint(){
        return end_;
    }

    /**
     * Sets the ending point of the projectile.
     *
     * @author Marcel Vangrootheest
     * @param point, the ending point set the end location as
     */
    void setEndPoint(QPointF* point){
        end_ = point;
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

private:
    size_t damage_;
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

#endif // PROJECTILE_H
