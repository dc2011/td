#ifndef TD_PROJECTILEINPUTCOMPONENTTYPES_H
#define TD_PROJECTILEINPUTCOMPONENTTYPES_H

#include "ProjectileInputComponent.h"

namespace td {

class ArrowProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    ArrowProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~ArrowProjectileInputComponent() {}
    
    virtual void update();
    void checkNPCCollision(QSet<Unit *> npcs);
};

class CannonProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    CannonProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~CannonProjectileInputComponent() {}

    /**
     * Updates the force for the projectile.
     *
     * @author Marcel Vangrootheest
     */
    virtual void update();
    void checkNPCCollision(QSet<Unit *> npcs);
};

class FireProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    FireProjectileInputComponent();
    virtual ~FireProjectileInputComponent() {}

    /**
     * Updates the force for the projectile.
     *
     * @author Marcel Vangrootheest
     */
    virtual void update();
    /**
     * Makes a force that will follow the path.
     *
     * @author Marcel Vangrootheest
     */
    void makeForce();
    void checkNPCCollision(QSet<Unit *> npcs);
private:
    int duration_;
    int increment_;
};

class TarProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    TarProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~TarProjectileInputComponent() {}

    /**
     * Updates the force for the projectile.
     *
     * @author Marcel Vangrootheest
     */
    virtual void update();
    void checkNPCCollision(QSet<Unit *> npcs);
};

class FlakProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    FlakProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~FlakProjectileInputComponent() {}

    /**
     * Updates the force for the projectile.
     *
     * @author Marcel Vangrootheest
     */
    virtual void update();
    void checkNPCCollision(QSet<Unit *> npcs);
};

} /* end namespace td */

#endif

