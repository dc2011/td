#ifndef TD_PROJECTILEINPUTCOMPONENTTYPES_H
#define TD_PROJECTILEINPUTCOMPONENTTYPES_H

#include "ProjectileInputComponent.h"
#include "../audio/SfxManager.h"

namespace td {

class ArrowProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    ArrowProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~ArrowProjectileInputComponent() {
        PLAY_SFX((QObject*)parent_, SfxManager::projectileHitArrow);
    }
    
    virtual void update();
};

class CannonProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    CannonProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~CannonProjectileInputComponent() {
        PLAY_SFX((QObject*)parent_, SfxManager::projectileHitCannon);
    }

    /**
     * Updates the force for the projectile.
     *
     * @author Marcel Vangrootheest
     */
    virtual void update();
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
private:
    int duration_;
    int increment_;
    int counter_;
};

class TarProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    TarProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~TarProjectileInputComponent() {
        PLAY_SFX((QObject*)parent_, SfxManager::projectileHitTar);
    }

    /**
     * Updates the force for the projectile.
     *
     * @author Marcel Vangrootheest
     */
    virtual void update();
};

class FlakProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    FlakProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~FlakProjectileInputComponent() {
        PLAY_SFX((QObject*)parent_, SfxManager::projectileHitFlak);
    }

    /**
     * Updates the force for the projectile.
     *
     * @author Marcel Vangrootheest
     */
    virtual void update();
};

} /* end namespace td */

#endif

