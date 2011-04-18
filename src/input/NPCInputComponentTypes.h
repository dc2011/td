#ifndef TD_NPCINPUTCOMPONENTTYPES_H
#define TD_NPCINPUTCOMPONENTTYPES_H

#include "NPCInputComponent.h"

namespace td {

class NormNPCInputComponent : public NPCInputComponent {
    Q_OBJECT

public:
    NormNPCInputComponent() : NPCInputComponent() {}
    virtual ~NormNPCInputComponent() {}
};

class SlowNPCInputComponent : public NPCInputComponent {
    Q_OBJECT

public:
    SlowNPCInputComponent() : NPCInputComponent() {}
    virtual ~SlowNPCInputComponent() {}
};

class ArmNPCInputComponent : public NPCInputComponent {
    Q_OBJECT

public:
    ArmNPCInputComponent() : NPCInputComponent() {}
    virtual ~ArmNPCInputComponent() {}
};

class FastNPCInputComponent : public NPCInputComponent {
    Q_OBJECT

public:
    FastNPCInputComponent() : NPCInputComponent() {}
    virtual ~FastNPCInputComponent() {}
};

class SwarmNPCInputComponent : public NPCInputComponent {
    Q_OBJECT

public:
    SwarmNPCInputComponent() : NPCInputComponent() {}
    virtual ~SwarmNPCInputComponent() {}
};

class FlyNPCInputComponent : public NPCInputComponent {
    Q_OBJECT

public:
    FlyNPCInputComponent() : NPCInputComponent() {}
    virtual ~FlyNPCInputComponent() {}
};

class BossNPCInputComponent : public NPCInputComponent {
    Q_OBJECT

public:
    BossNPCInputComponent() : NPCInputComponent() {}
    virtual ~BossNPCInputComponent() {}
};

} /* end namespace td */

#endif

