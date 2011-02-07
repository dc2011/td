#ifndef PLAYERPHYSICSCOMPONENT_H
#define PLAYERPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "Player.h"

class PlayerPhysicsComponent : public PhysicsComponent {
public:
    PlayerPhysicsComponent();
    virtual ~PlayerPhysicsComponent();
    void ApplyForce(Player*);
    void ApplyVelocity(Player*);
    
public slots:
    virtual void Update(Player*);
    
private:
    /* data */
    const int accel_;
    const int decel_;
    const int maxVelocity_;
};

#endif
