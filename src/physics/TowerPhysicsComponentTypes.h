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
    void fire();
};

class ArrowTowerL2PhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    ArrowTowerL2PhysicsComponent(Tower* tower);
    virtual ~ArrowTowerL2PhysicsComponent() { }
    bool isValidTarget(Unit *);
    void fire();
};

class ArrowTowerL3PhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    ArrowTowerL3PhysicsComponent(Tower* tower);
    virtual ~ArrowTowerL3PhysicsComponent() { }
    bool isValidTarget(Unit *);
    void fire();
};

class CannonTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    CannonTowerPhysicsComponent(Tower* tower);
    virtual ~CannonTowerPhysicsComponent() { }
    bool isValidTarget(Unit *);
    void fire();
};

class CannonTowerL2PhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    CannonTowerL2PhysicsComponent(Tower* tower);
    virtual ~CannonTowerL2PhysicsComponent() { }
    bool isValidTarget(Unit *);
    void fire();
};

class CannonTowerL3PhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    CannonTowerL3PhysicsComponent(Tower* tower);
    virtual ~CannonTowerL3PhysicsComponent() { }
    bool isValidTarget(Unit *);
    void fire();
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
protected:
    bool foundTarget_;
    bool ready_;
};

class FlameTowerL2PhysicsComponent : public FlameTowerPhysicsComponent {
    Q_OBJECT

public:
    FlameTowerL2PhysicsComponent(Tower* tower);
    virtual ~FlameTowerL2PhysicsComponent() { }
    void fire();
};

class FlameTowerL3PhysicsComponent : public FlameTowerPhysicsComponent {
    Q_OBJECT

public:
    FlameTowerL3PhysicsComponent(Tower* tower);
    virtual ~FlameTowerL3PhysicsComponent() { }
    void fire();
};

class TarTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    TarTowerPhysicsComponent(Tower* tower);
    virtual ~TarTowerPhysicsComponent() { }
    virtual void update(GameObject *tower);
    bool isValidTarget(Unit *);
    void fire();
};

class TarTowerL2PhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    TarTowerL2PhysicsComponent(Tower* tower);
    virtual ~TarTowerL2PhysicsComponent() { }
    virtual void update(GameObject *tower);
    bool isValidTarget(Unit *);
    void fire();
};

class TarTowerL3PhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    TarTowerL3PhysicsComponent(Tower* tower);
    virtual ~TarTowerL3PhysicsComponent() { }
    virtual void update(GameObject *tower);
    bool isValidTarget(Unit *);
    void fire();
};

class FlakTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    FlakTowerPhysicsComponent(Tower* tower);
    virtual ~FlakTowerPhysicsComponent() { }
    bool isValidTarget(Unit *);
    void fire();
};

class FlakTowerL2PhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    FlakTowerL2PhysicsComponent(Tower* tower);
    virtual ~FlakTowerL2PhysicsComponent() { }
    bool isValidTarget(Unit *);
    void fire();
};

class FlakTowerL3PhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    FlakTowerL3PhysicsComponent(Tower* tower);
    virtual ~FlakTowerL3PhysicsComponent() { }
    bool isValidTarget(Unit *);
    void fire();
};

} /* end namespace td */

#endif

