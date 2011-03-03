#ifndef NPCPHYSICSCOMPONENT_H
#define NPCPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "NPC.h"
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

public slots:
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
    float accel_;
    float decel_;
    float maxVelocity_;
};


#endif // NPCPHYSICSCOMPONENT_H
