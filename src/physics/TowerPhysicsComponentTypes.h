#ifndef TD_TOWERPHYSICSCOMPONENTTYPES_H
#define TD_TOWERPHYSICSCOMPONENTTYPES_H

#include "TowerPhysicsComponent.h"

namespace td {

class ArrowTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    ArrowTowerPhysicsComponent(Tower* tower);
    virtual ~ArrowTowerPhysicsComponent() { }
    virtual void update(GameObject *tower);
    void fire();
};

class CannonTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    CannonTowerPhysicsComponent(Tower* tower);
    virtual ~CannonTowerPhysicsComponent() { }
    virtual void update(GameObject *tower);
    void fire();
};

class FlameTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    FlameTowerPhysicsComponent(Tower* tower);
    virtual ~FlameTowerPhysicsComponent() { }
    virtual void update(GameObject *tower);
    void findDirectionToShoot();
    void useDirection();
    void applyDuration();
    void fire();
private:
    int duration_;
    /** The line between the tower and its current target. */
    QLineF flamePath_;
    QPointF rotationEndPoint_;
    /** The enemy that's currently being tracked by the tower. */
    Unit* endPoint_;

};

class TarTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    TarTowerPhysicsComponent(Tower* tower);
    virtual ~TarTowerPhysicsComponent() { }
    virtual void update(GameObject *tower);
    void fire();
};

class FlakTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    FlakTowerPhysicsComponent(Tower* tower);
    virtual ~FlakTowerPhysicsComponent() { }
    virtual void update(GameObject *tower);
    void fire();
};

} /* end namespace td */

#endif

