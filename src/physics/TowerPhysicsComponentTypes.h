#ifndef TD_TOWERPHYSICSCOMPONENTTYPES_H
#define TD_TOWERPHYSICSCOMPONENTTYPES_H

#include "TowerPhysicsComponent.h"

namespace td {

class ArrowTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    ArrowTowerPhysicsComponent();
    virtual ~ArrowTowerPhysicsComponent() { }
};

class CannonTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    CannonTowerPhysicsComponent();
    virtual ~CannonTowerPhysicsComponent() { }
};

class FlameTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    FlameTowerPhysicsComponent();
    virtual ~FlameTowerPhysicsComponent() { }
};

class TarTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    TarTowerPhysicsComponent();
    virtual ~TarTowerPhysicsComponent() { }
};

class FlakTowerPhysicsComponent : public TowerPhysicsComponent {
    Q_OBJECT

public:
    FlakTowerPhysicsComponent();
    virtual ~FlakTowerPhysicsComponent() { }
};

} /* end namespace td */

#endif

