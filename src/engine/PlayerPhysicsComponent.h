#ifndef PLAYERPHYSICSCOMPONENT_H
#define PLAYERPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "Player.h"

class PlayerPhysicsComponent : public PhysicsComponent {
public:
    PlayerPhysicsComponent();
    virtual ~PlayerPhysicsComponent();
    
public slots:
    virtual void Update(Player*);
    
private:
    /* data */
};

#endif
