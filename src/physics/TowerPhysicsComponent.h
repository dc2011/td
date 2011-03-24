#ifndef TOWERPHYSICSCOMPONENT_H
#define TOWERPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "../engine/NPC.h"
#include "../engine/Map.h"
#include "../engine/CDriver.h"
#include <QPointF>
#include <QLineF>
#include <QSet>

namespace td {

class Tower;

/** Movement Physics for basic Tower */
class TowerPhysicsComponent: public PhysicsComponent {
    Q_OBJECT

public:
    TowerPhysicsComponent(Tower* tower, size_t fireInterval, int radius);
    virtual ~TowerPhysicsComponent();

    /**
     * Applies a direction to the position.
     * This function uses velocity to find angle, pos
     *
     * @author Joel Stewart
     * @param Tower, pointer to the Tower object
     */
    void applyDirection(GameObject* tower);

    /**
     * This updates the physics properties of Tower.
     */
    virtual void update(GameObject* tower);

    /**
     * Finds the next target.
     *
     * @author Joel Stewart, Dean Morin
     */
    void findTarget();

    /**
     * Sets NPCs from the towers coords.
     *
     * @author Joel Stewart
     * @param Tower, pointer to the Tower object
     * @param Radius, size of radius around tower
     */
    void setNPCs(GameObject* tower, int radius) {
        Map* map = tower->getDriver()->getGameMap();
        enemies_ = map->getUnits(tower->getPos().x() ,tower->getPos().y() , radius);
    }

    /**
     * Checks to see if the tower can fire, and creates a projectile if it can.
     *
     * @author Dean Morin
     */
    void fire();

    /**
     * returns current enemies in sight.
     *
     * @author Joel Stewart
     */
    QSet<Unit*> getEnemies() {
        return enemies_;
    }

    /**
     * Set current Target
     *
     * @author Joel Stewart
     * @param Unit, pointer to target your setting
     */
    void setTarget(Unit* target) {
        target_ = target;
    }

    /**
     * gets current target.
     *
     * @author Joel Stewart
     * @return current target
     */
    Unit* getTarget() {
        return target_;
    }

    /**
     * Sets radius value of tower.
     *
     * @author Joel Stewart
     * @param radius sets radius_
     */
    void setRadius(int radius) {
        radius_ = radius;
    }

    /**
     * returns radius value of the tower
     *
     * @author Joel Stewart
     * @return radius value
     */
    int getRadius() {
        return radius_;
    }

private:
    /** The tower that this component defines. */
    Tower* tower_;
    QSet<Unit*> enemies_;
    Unit* target_;
    QLineF projectilePath_;
    
protected:
    /** The number of ticks beween each shot. */
    size_t fireInterval_;

    /** The range of the tower. */
    int radius_;
    
    /** Number of game timer ticks before this tower can fire a projectile. */
    size_t fireCountdown_;

signals:
    /**
     * Connected to the createProjectile() slot in CDriver.
     *
     * @author Dean Morin
     * @param source The position of the tower firing the projectile.
     * @param target The current position of the enemy that the tower has 
     * tageted.
     */
    void fireProjectile(QPointF source, QPointF target);

public slots:
    /**
     * Sets the target_ member to null if the NPC dies.
     *
     * Connected to signalNPCDied() in the NPC class.
     *
     * @author Dean Morin
     */
    void targetDied();
};

} /* end namespace td */

#endif
