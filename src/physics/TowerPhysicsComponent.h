#ifndef TOWERPHYSICSCOMPONENT_H
#define TOWERPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "../engine/NPC.h"
#include "../engine/Map.h"
#include "../engine/CDriver.h"
#include <QPointF>
#include <QSet>

namespace td {

class Tower;

/** Movement Physics for basic Tower */
class TowerPhysicsComponent: public PhysicsComponent {
    Q_OBJECT

public:
    TowerPhysicsComponent(Tower* tower, size_t fireInterval);
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
     * Gathers Targets.
     *
     * @author Joel Stewart
     * @param Tower, pointer to the Tower object
     */
    void findTargets(GameObject* tower, int radius);

    /**
     * Sets NPCs from the towers coords.
     *
     * @author Joel Stewart
     * @param Tower, pointer to the Tower object
     * @param Radius, size of radius around tower
     */
    void setNPCs(GameObject* tower, int radius) {
#ifndef SERVER
        Map* map = CDriver::instance()->getGameMap();
        enemies_ = map->getUnits(tower->getPos().x() ,tower->getPos().y() , radius);
#endif
    }

    /**
     * Checks to see if the tower can fire, and creates a projectile if it can.
     *
     * @author Dean Morin
     */
    void fire();

    QSet<Unit*> getNPCs() {
        return enemies_;
    }

    void setTarget(Unit* enemy) {
        enemy_ = enemy;
    }

    Unit* getEnemy() {
        return enemy_;
    }

    void setRadius(int radius) {
        radius_ = radius;
    }

    int getRadius() {
        return radius_;
    }

private:
    /** The tower that this component defines. */
    Tower* tower_;
    int radius_;
    QSet<Unit*> enemies_;
    Unit* enemy_;
    
protected:
    /** The number of ticks beween each shot. */
    size_t fireInterval_;

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
};

} /* end namespace td */

#endif
