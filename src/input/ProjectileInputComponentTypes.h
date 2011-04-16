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
        PLAY_SFX(this, SfxManager::projectileHitArrow);
    }
    
    virtual void update();
    void checkNPCCollision(QSet<Unit *> npcs);
};

class CannonProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    CannonProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~CannonProjectileInputComponent() {
        PLAY_SFX(this, SfxManager::projectileHitCannon);
    }

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
    int counter_;
};

class TarProjectileInputComponent : public ProjectileInputComponent {
    Q_OBJECT

public:
    TarProjectileInputComponent() : ProjectileInputComponent() {}
    virtual ~TarProjectileInputComponent() {
        PLAY_SFX(this, SfxManager::projectileHitTar);
    }

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
    virtual ~FlakProjectileInputComponent() {
        PLAY_SFX(this, SfxManager::projectileHitFlak);
    }

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

