#ifndef PLAYER_H
#define PLAYER_H

#include <QEvent>
#include <QKeyEvent>

#include "Unit.h"
#include "PlayerInputComponent.h"
#include "CollisionComponent.h"
#include "../graphics/PlayerGraphicsComponent.h"

class Player : public Unit {
    Q_OBJECT
public:
    Player(InputComponent* input, PhysicsComponent* physics, 
           GraphicsComponent* graphics, CollisionComponent* collision);
    
    virtual void update();
private:
    CollisionComponent* collision_;
};

#endif
