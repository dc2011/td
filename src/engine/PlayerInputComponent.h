#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include <QVector2D>
#include "InputComponent.h"
#include "Unit.h"

class PlayerInputComponent : public InputComponent {
public:
    PlayerInputComponent();
    virtual ~PlayerInputComponent();
    
    void update();
    void processDirectionKey(Unit*, int, int);
        
private:
};

#endif
