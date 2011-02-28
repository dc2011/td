#ifndef TOWER_H
#define TOWER_H

#include "TileExtension.h"
#include "PhysicsComponent.h"

namespace td {

class Tower : public TileExtension {
    Q_OBJECT

private:
    PhysicsComponent* physics_;
    
public:
    Tower(PhysicsComponent* physics, GraphicsComponent* graphics);
    virtual ~Tower() {}
};
} // end of namespace td

#endif

