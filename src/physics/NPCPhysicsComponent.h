#ifndef NPCPHYSICSCOMPONENT_H
#define NPCPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"

namespace td {

class NPC;

class NPCPhysicsComponent : public PhysicsComponent {
public:
    NPCPhysicsComponent();
    virtual ~NPCPhysicsComponent();
    /**
     * Applies a force to the velocity
     * If force is 1 or -1:
     *      Acceleration applied on direction to velocity.
     *      Deceleration is added if velocity is approaching 0.
     * If force is 0:
     *      Deceleration is applied to velocity while velocity approaches 0.
     *
     * @author Marcel Vangrootheest
     * @param NPC*, pointer to the NPC object
     */
    void applyForce(NPC*);
    /**
     * Applies a velocity to the position.
     * This function just adds the vector velocity to the point, pos
     *
     * @author Marcel Vangrootheest
     * @param NPC*, pointer to the NPC object
     */
    void applyVelocity(NPC*);
    /**
     * Applies a direction to the position.
     * This function uses velocity to find angle, pos
     *
     * @author Joel Stewart
     * @param NPC*, pointer to the NPC object
     */
    void applyDirection(NPC*);

    /**
     * Returns the defined maximum velocity of the NPC.
     *
     * @author Marcel Vangrootheest
     * @return the float maximum velocity
     */
    float getMaxVelocity() {
        return maxVelocity_;
    }
    /**
     * Sets the maximum velocity of NPC to velocity.
     *
     * @author Marcel Vangrootheest
     * @param velocity, the new maximum velocity
     */
    void setMaxVelocity(float velocity) {
        maxVelocity_ = velocity;
    }

    /**
     * This updates the physics properties of NPC.
     * Applies force to velocity, applies velocity to position.
     *
     * @author Marcel Vangrootheest
     * @param Unit*, pointer to the Unit(NPC object)
     */
    virtual void update(Unit*);

private:
    /* data */
    /** The amount to add to velocity when a force is applied. */
    float accel_;
    /** The amount to subtract from velocity when no force is applied. */
    float decel_;
    /** The maximum amount a position can change when a force is applied. */
    float maxVelocity_;
};

} /* end namespace td */

#endif // NPCPHYSICSCOMPONENT_H
