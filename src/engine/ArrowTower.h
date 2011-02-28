#ifndef ARROWTOWER_H
#define ARROWTOWER_H

#include "Tower.h"

namespace td {

class ArrowTower : public Tower {
    Q_OBJECT

public:
    ArrowTower(PhysicsComponent* physics, GraphicsComponent* graphics);
    virtual ~ArrowTower() {}
};
} // end of namespace td

#endif

