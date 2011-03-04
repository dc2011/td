#ifndef PLAYER_H
#define PLAYER_H

#include <QEvent>
#include <QKeyEvent>

#include "Unit.h"
#include "PlayerInputComponent.h"
#include "../graphics/PlayerGraphicsComponent.h"

class Player : public Unit {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kPlayer;
    }

public:
    Player();
    Player(InputComponent* input, PhysicsComponent* physics, 
           GraphicsComponent* graphics);
    virtual ~Player() {}

    virtual void update();
};

#endif
