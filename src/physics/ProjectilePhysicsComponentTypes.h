#ifndef TD_PROJECTILEPHYSICSCOMPONENTTYPES_H
#define TD_PROJECTILEPHYSICSCOMPONENTTYPES_H

#include "ProjectilePhysicsComponent.h"

namespace td {

class Projectile;

class ArrowProjectilePhysicsComponent : public ProjectilePhysicsComponent {
    Q_OBJECT

public:
    ArrowProjectilePhysicsComponent();
    virtual ~ArrowProjectilePhysicsComponent() {}
    
    void setScale(Projectile* projectile);
};

class CannonProjectilePhysicsComponent : public ProjectilePhysicsComponent {
    Q_OBJECT

public:
    CannonProjectilePhysicsComponent();
    virtual ~CannonProjectilePhysicsComponent() {}
    
    void setScale(Projectile* projectile);
};

class FireProjectilePhysicsComponent : public ProjectilePhysicsComponent {
    Q_OBJECT

public:
    FireProjectilePhysicsComponent();
    virtual ~FireProjectilePhysicsComponent() {}
    
    void setScale(Projectile* projectile);
};

class TarProjectilePhysicsComponent : public ProjectilePhysicsComponent {
    Q_OBJECT

public:
    TarProjectilePhysicsComponent();
    virtual ~TarProjectilePhysicsComponent() {}
    
    void setScale(Projectile* projectile);
};

class FlakProjectilePhysicsComponent : public ProjectilePhysicsComponent {
    Q_OBJECT

public:
    FlakProjectilePhysicsComponent();
    virtual ~FlakProjectilePhysicsComponent() {}
    
    void setScale(Projectile* projectile);
};

} /* end namespace td */

#endif

