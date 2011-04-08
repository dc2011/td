#ifndef TD_PROJECTILEINPUTCOMPONENTTYPES_H
#define TD_PROJECTILEINPUTCOMPONENTTYPES_H

#include "ProjectileInputComponent.h"

namespace td {

class ArrowProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    ArrowProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~ArrowProjectileInputComponent() {}
};

class CannonProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    CannonProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~CannonProjectileInputComponent() {}
};

class FireProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    FireProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~FireProjectileInputComponent() {}
};

class TarProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    TarProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~TarProjectileInputComponent() {}
};

class FlakProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    FlakProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~FlakProjectileInputComponent() {}
};

} /* end namespace td */

#endif

