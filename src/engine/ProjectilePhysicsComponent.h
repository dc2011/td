#ifndef PROJECTILEPHYSICSCOMPONENT_H
#define PROJECTILEPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "Projectile.h"
class ProjectilePhysicsComponent : public PhysicsComponent {
public:
    ProjectilePhysicsComponent();
    virtual ~ProjectilePhysicsComponent();
    /**
     * Applies a velocity to the position.
     * This function just adds the vector velocity to the point, pos
     *
     * @author Marcel Vangrootheest , Joel Stewart
     * @param Projectile*, pointer to the projectile object
     */
    void applyVelocity(Projectile*);
    /**
     * Applies a direction to the position.
     * This function uses velocity to find angle, pos
     *
     * @author Joel Stewart , Marcel Vangrootheest
     * @param Projectile*, pointer to the projectile object
     */
    void setAngle(Projectile*);
    /**
     * Changes scale to simulate an arc.
     * This function uses length of path and maxVelocity to set duration.
     * Scale is changed based on duration.
     *
     * @author Marcel Vangrootheest
     * @param Projectile*, pointer to the projectile object
     */
    void setScale(Projectile*);
public slots:
    virtual void update(Unit*);

private:
    float maxVelocity_;
    double duration_;
    double increment_;
};

#endif
