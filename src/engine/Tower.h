#ifndef TOWER_H
#define TOWER_H

#include "TileExtension.h"
#include "Effect.h"
#include "../graphics/TowerGraphicsComponent.h"

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

public:
    virtual ~Tower() {}
    
    virtual void update();

private:
    QList<Effect*> effects_;
};
} // end of namespace td

#endif

