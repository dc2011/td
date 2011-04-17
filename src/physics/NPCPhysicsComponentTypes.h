#ifndef TD_NPCPHYSICSCOMPONENTTYPES_H
#define TD_NPCPHYSICSCOMPONENTTYPES_H

#include "NPCPhysicsComponent.h"

namespace td {

class NormNPCPhysicsComponent : public NPCPhysicsComponent {
    Q_OBJECT

public:
    NormNPCPhysicsComponent();
    virtual ~NormNPCPhysicsComponent() {}
};

class SlowNPCPhysicsComponent : public NPCPhysicsComponent {
    Q_OBJECT

public:
    SlowNPCPhysicsComponent();
    virtual ~SlowNPCPhysicsComponent() {}
};

class ArmNPCPhysicsComponent : public NPCPhysicsComponent {
    Q_OBJECT

public:
    ArmNPCPhysicsComponent();
    virtual ~ArmNPCPhysicsComponent() {}
};

class FastNPCPhysicsComponent : public NPCPhysicsComponent {
    Q_OBJECT

public:
    FastNPCPhysicsComponent();
    virtual ~FastNPCPhysicsComponent() {}
};

class SwarmNPCPhysicsComponent : public NPCPhysicsComponent {
    Q_OBJECT

public:
    SwarmNPCPhysicsComponent();
    virtual ~SwarmNPCPhysicsComponent() {}
};

class FlyNPCPhysicsComponent : public NPCPhysicsComponent {
    Q_OBJECT

public:
    FlyNPCPhysicsComponent();
    virtual ~FlyNPCPhysicsComponent() {}
};

class BossNPCPhysicsComponent : public NPCPhysicsComponent {
    Q_OBJECT

public:
    BossNPCPhysicsComponent();
    virtual ~BossNPCPhysicsComponent() {}
};

} /* end namespace td */

#endif

