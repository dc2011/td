#ifndef NPCPHYSICSCOMPONENT_H
#define NPCPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include <QVector>

namespace td {

class NPC;
class CDriver;

class NPCPhysicsComponent : public PhysicsComponent {
public:
    NPCPhysicsComponent(float a, float d, float mV);
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
     * Sets the acceleration of NPC to accel
     * (Mainly for Effects)
     *
     * @author Marcel Vangrootheest
     * @param accel the new acceleration amount
     */
    void setAccel(float accel) {
        accel_ = accel;
    }

    /**
     * Sets the deceleration of NPC to decel
     * (Mainly for Effects)
     *
     * @author Marcel Vangrootheest
     * @param decel the new deceleration amount
     */
    void setDecel(float decel) {
        decel_ = decel;
    }

    /**
     * This updates the physics properties of NPC.
     * Applies force to velocity, applies velocity to position.
     *
     * @author Marcel Vangrootheest
     * @param Unit*, pointer to the Unit(NPC object)
     */
    virtual void update(GameObject*);

protected:
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
