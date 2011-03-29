#ifndef PROJECTILEPHYSICSCOMPONENT_H
#define PROJECTILEPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include <QSet>
#include "../engine/Effect.h"
#include "../engine/Unit.h"

namespace td {

class Projectile;

/** Movement Physics for basic Projectile */
class ProjectilePhysicsComponent : public PhysicsComponent {
public:
    ProjectilePhysicsComponent();
    virtual ~ProjectilePhysicsComponent();
    /**
     * Applies a force to the velocity
     * If force is 1 or -1:
     *      Acceleration applied on direction to velocity.
     *      Deceleration is added if velocity is approaching 0.
     * If force is 0:
     *      Deceleration is applied to velocity while velocity approaches 0.
     *
     * @author Marcel Vangrootheest
     * @param projectile, pointer to the NPC object
     */
    void applyForce(Projectile* projectile);
    /**
     * Applies a velocity to the position.
     * This function just adds the vector velocity to the point, pos
     *
     * @author Marcel Vangrootheest , Joel Stewart
     * @param projectile, pointer to the projectile object
     */
    void applyVelocity(Projectile* projectile);
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
    virtual void update(GameObject* projectile);


private:
    /** Velocity of the projectile. */
    float maxVelocity_;
    /**  Time of life for the projectile. */
    double duration_;
    /** Amount to increment the scale by per tick. */
    double increment_;
    /** Amount to increase velocity by when force applied. */
    double accel_;
    /** Amount to decrease velocity when force not applied. */
    double decel_;
};

} /* end namespace td */

#endif
