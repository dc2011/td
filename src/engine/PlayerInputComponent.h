#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include "InputComponent.h"

class PlayerInputComponent : public InputComponent {
public:
    PlayerInputComponent();
    virtual ~PlayerInputComponent();
    
    void Update();
    
private:
};

#endif
