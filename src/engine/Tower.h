#ifndef TOWER_H
#define TOWER_H

#include "TileExtension.h"
#include "PhysicsComponent.h"

namespace td {

class Tower : public TileExtension {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kTower;
    }

private:
    PhysicsComponent* physics_;
    
public:
    Tower(PhysicsComponent* physics, GraphicsComponent* graphics);
    virtual ~Tower() {}
};
} // end of namespace td

#endif

