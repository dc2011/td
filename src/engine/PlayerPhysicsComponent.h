#ifndef PLAYERPHYSICSCOMPONENT_H
#define PLAYERPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "Player.h"

class PlayerPhysicsComponent : public PhysicsComponent {
public:
    PlayerPhysicsComponent();
    virtual ~PlayerPhysicsComponent();
    void applyForce(Player*);
    void applyVelocity(Player*);
    
public slots:
    virtual void update(Player*);
    
private:
    /* data */
    const int accel_;
    const int decel_;
    const int maxVelocity_;
};

#endif
