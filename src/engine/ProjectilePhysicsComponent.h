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
     * @param projectile, pointer to the projectile object
     */
    void applyVelocity(Projectile* projectile);
    /**
     * Applies a direction to the position.
     * This function uses velocity to find angle, pos
     *
     * @author Joel Stewart , Marcel Vangrootheest
     * @param projectile, pointer to the projectile object
     */
    void applyDirection(Projectile* projectile);
    /**
     * Changes scale to simulate an arc.
     * This function uses length of path and maxVelocity to set duration.
     * Scale is changed based on duration.
     *
     * @author Marcel Vangrootheest
     * @param projectile, pointer to the projectile object
     */
    void setScale(Projectile* projectile);

    /**
     * Updates the projectile's position, orientation and scale
     * until the end of it's path.
     *
     * @author Marcel Vangrootheest
     * @param projectile, pointer to the projectile object
     */
    virtual void update(Unit* projectile);

private:
    /** Velocity of the projectile. */
    float maxVelocity_;
    /**  Time of life for the projectile. */
    double duration_;
    /** Amount to increment the scale by per tick. */
    double increment_;
};

#endif
