#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include <QEvent>
#include <QKeyEvent>
#include "InputComponent.h"

class PlayerInputComponent : public InputComponent {
public:
    PlayerInputComponent();
    virtual ~PlayerInputComponent();
    
    void Update();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    
private:
};

#endif
