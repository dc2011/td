#ifndef PLAYER_H
#define PLAYER_H

#include <QEvent>
#include <QKeyEvent>

#include "Unit.h"
#include "PlayerInputComponent.h"

class Player : public Unit {
    Q_OBJECT
public:
    Player(InputComponent* input, PhysicsComponent* physics, 
           GraphicsComponent* graphics);
    
    virtual void update();
};

#endif
