#ifndef PLAYER_H
#define PLAYER_H

#include <QEvent>
#include <QKeyEvent>

#include "Unit.h"
#include "../input/PlayerInputComponent.h"
#include "CollisionComponent.h"
#include "../graphics/PlayerGraphicsComponent.h"
#include "../physics/PlayerPhysicsComponent.h"

namespace td {

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
    virtual ~Player() {}

    virtual void update();
};

}

#endif
