#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include <QVector2D>
#include "InputComponent.h"
#include "../engine/Unit.h"

namespace td {

class Player;

class PlayerInputComponent : public InputComponent {
    Q_OBJECT
    
public:
    PlayerInputComponent();
    virtual ~PlayerInputComponent();
    
    void update();
    void processDirectionKey(int, int);
    void setParent(Unit*);

public slots:
    void keyPressed(int);
    void keyReleased(int);
    void playerMovement(bool);

private:
    Player* parent_;
    bool menuIsOpen_;
};

} /* end namespace td */

#endif
