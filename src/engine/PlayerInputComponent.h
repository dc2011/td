#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include <QVector2D>
#include "InputComponent.h"
#include "Unit.h"

class Player;
class PlayerInputComponent : public InputComponent {
public:
    PlayerInputComponent();
    virtual ~PlayerInputComponent();
    
    void update();
    void processDirectionKey(int, int);
    void setParent(Unit*);

protected:
    bool eventFilter(QObject *, QEvent *);
        
private:
    Player* parent_;
};

#endif
