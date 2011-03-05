#ifndef ARROWTOWER_H
#define ARROWTOWER_H

#include "Tower.h"

namespace td {

class ArrowTower : public Tower {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kArrowTower;
    }

public:
    virtual ~ArrowTower() {}
};
} // end of namespace td

#endif

