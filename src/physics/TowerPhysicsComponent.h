/** Movement Physics for basic Projectile */
#ifndef TOWERPHYSICSCOMPONENT_H
#define TOWERPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "../engine/CDriver.h"
#include "../engine/GameObject.h"
#include "../engine/Unit.h"
#include "../engine/Map.h"
#include "../engine/TileExtension.h"
#include <QPointF>
#include <set>

namespace td {

class TowerPhysicsComponent:public TileExtension {
    Q_OBJECT

public:
    TowerPhysicsComponent();
    virtual ~TowerPhysicsComponent() {}

    /**
     * Applies a direction to the position.
     * This function uses velocity to find angle, pos
     *
     * @author Joel Stewart
     * @param Tower, pointer to the Tower object
     */
    void applyDirection(GameObject* tower);

    /**
     * This updates the physics properties of Tower.\
     */
    virtual void update(GameObject* tower);

    void setNPCs(GameObject* tower, int radius) {
        enemies_ = Map.getUnits(tower->getPos().x() ,tower->getPos().y() , radius);
    }

    std::set<Unit*> getNPCs() {
        return enemies_;
    }

    void setTarget(Unit* enemy) {
        enemy_ = enemy;
    }

    Unit* getEnemy() {
        return enemy_;
    }

private:
    /* data */
    std::set<Unit*> enemies_;
    Unit* enemy_;
};

} /* end namespace td */

#endif
