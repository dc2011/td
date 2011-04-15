#ifndef TD_TOWERPHYSICSCOMPONENTTYPES_H
#define TD_TOWERPHYSICSCOMPONENTTYPES_H

#include "TowerPhysicsComponent.h"

namespace td {

class ArrowTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    ArrowTowerPhysicsComponent(Tower* tower);
    virtual ~ArrowTowerPhysicsComponent() { }
    bool isValidTarget(Unit *);
};

class CannonTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    CannonTowerPhysicsComponent(Tower* tower);
    virtual ~CannonTowerPhysicsComponent() { }
    bool isValidTarget(Unit *);
};

class FlameTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    FlameTowerPhysicsComponent(Tower* tower);
    virtual ~FlameTowerPhysicsComponent() { }
    virtual void update(GameObject *tower);
    void findDirectionToShoot();
    bool isValidTarget(Unit *);
    void fire();
private:
    bool foundTarget_;
    bool ready_;

};

class TarTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    TarTowerPhysicsComponent(Tower* tower);
    virtual ~TarTowerPhysicsComponent() { }
    virtual void update(GameObject *tower);
    bool isValidTarget(Unit *);
};

class FlakTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    FlakTowerPhysicsComponent(Tower* tower);
    virtual ~FlakTowerPhysicsComponent() { }
    bool isValidTarget(Unit *);
};

} /* end namespace td */

#endif

