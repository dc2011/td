#ifndef COLLECTABLEPHYSICSCOMPONENT_H
#define COLLECTABLEPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include <QSet>
#include "../engine/Effect.h"
#include "../engine/Unit.h"

//TEMP
#include "../engine/Collectable.h"

namespace td {

class Collectable;

/** Movement Physics for basic Collectable */
class CollectablePhysicsComponent : public PhysicsComponent {

public:
    CollectablePhysicsComponent();
    virtual ~CollectablePhysicsComponent();

    /**
     * Applies a force to the velocity
     * If force is 1 or -1:
     *      Acceleration applied on direction to velocity.
     *      Deceleration is added if velocity is approaching 0.
     * If force is 0:
     *      Deceleration is applied to velocity while velocity approaches 0.
     *
     * @author Marcel Vangrootheest
     * @param collectable, pointer to the NPC object
     */
    void applyForce(Collectable* collectable);

    /**
     * Applies a velocity to the position.
     * This function just adds the vector velocity to the point, pos
     *
     * @author Marcel Vangrootheest , Joel Stewart
     * @param collectable, pointer to the collectable object
     */
    void applyVelocity(Collectable* collectable);

    /**
     * Changes scale to simulate an arc.
     * This function uses length of path and maxVelocity to set duration.
     * Scale is changed based on duration.
     *
     * @author Marcel Vangrootheest
     * @param collectable, pointer to the collectable object
     */
    virtual void setScale(Collectable* collectable);

    /**
     * Updates the collectable's position, orientation and scale
     * until the end of it's path.
     *
     * @author Marcel Vangrootheest
     * @param collectable, pointer to the collectable object
     */
    virtual void update(GameObject* collectable);

protected:
    /** Velocity of the collectable. */
    float maxVelocity_;

    /** Amount to increase velocity by when force applied. */
    double accel_;

    /** Amount to decrease velocity when force not applied. */
    double decel_;

    /**  Time of life for the collectable. */
    double duration_;

    /** Amount to increment the scale by per tick. */
    double increment_;
};

} /* end namespace td */

#endif
