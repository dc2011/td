#ifndef TD_TOWER_H
#define TD_TOWER_H

#include "TileExtension.h"

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
    Tower(QObject* parent = 0);
    virtual ~Tower() {}
    virtual void initComponents();
    virtual void update();

    /**
     * TODO: remove once objects are being created by the server (it's a hack).
     */
    virtual void initComponents(int towerType);

private:

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

