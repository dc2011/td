#ifndef TD_TOWER_H
#define TD_TOWER_H

#include "TileExtension.h"
#include "../graphics/TowerGraphicsComponent.h"
#include "../physics/TowerPhysicsComponent.h"

namespace td {

class Effect;

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
    virtual void initComponents();
    virtual void update();

    /**
     * TODO: remove once objects are being created by the server (it's a hack).
     */
    virtual void initComponents(int towerType);

    /**
     * Sets the tower type (arrow, cannon, tar, flame, or flak).
     *
     * @author Darryl Pogue
     * @param The type of tower.
     */
    void setType(int type) {
        type_ = type;
    }

private:
    int type_;

    /**
     * Set to false when the tower is initialized. On the first network read, 
     * this flag will be checked, the components will be actually initialized,
     * and the flag will be set to true. This is needed because towers require
     * an argument (the tower type) in order to know what type of tower to
     * become.
     */
    bool componentsInitialized_;
};
} // end of namespace td

#endif

