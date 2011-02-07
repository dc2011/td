#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"

class Player : public Unit {
    Q_OBJECT
public:
    Player(InputComponent* input, PhysicsComponent* physics);
    
    virtual void Update();
    
};

#endif
