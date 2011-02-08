#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include <QVector2D>
#include "InputComponent.h"
#include "Unit.h"

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

private:
    Player* parent_;
};

#endif
