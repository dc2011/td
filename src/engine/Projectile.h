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
     * @author Pan Khantidhara
     * @param physics Physic component.
     * @param graphic Graphic component.
     * @param sender Unit, which starts the projectile
     * @param receiver Unit, which the projectile ends
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

    QPointF* getStartPoint(){
        return start_;
    }

    void setStartPoint(QPointF* point){
        start_ = point;
    }

    QPointF* getEndPoint(){
        return end_;
    }

    void setEndPoint(QPointF* point){
        end_ = point;
    }

    QLineF& getPath() {
        return path_;
    }

    void setPath(QLineF& path) {
       path_ = path;
    }

private:
    size_t damage_;
    QPointF* start_;
    QPointF* end_;
    QLineF path_;
};

#endif // PROJECTILE_H
