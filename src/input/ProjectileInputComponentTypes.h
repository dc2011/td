#ifndef TD_PROJECTILEINPUTCOMPONENTTYPES_H
#define TD_PROJECTILEINPUTCOMPONENTTYPES_H

#include "ProjectileInputComponent.h"

namespace td {

class ArrowProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    ArrowProjectileInputComponent() : ProjectileInputComponent(){}
    virtual ~ArrowProjectileInputComponent() {}
    
    void update();
    void checkNPCCollision(QSet<Unit *> npcs);
};

class CannonProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    CannonProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~CannonProjectileInputComponent() {}

    void update();
    void checkNPCCollision(QSet<Unit *> npcs);
};

class FireProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    FireProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~FireProjectileInputComponent() {}

    void checkNPCCollision(QSet<Unit *> npcs);
};

class TarProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    TarProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~TarProjectileInputComponent() {}

    void update();
    void checkNPCCollision(QSet<Unit *> npcs);
};

class FlakProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    FlakProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~FlakProjectileInputComponent() {}

    void update();
    void checkNPCCollision(QSet<Unit *> npcs);
};

} /* end namespace td */

#endif

