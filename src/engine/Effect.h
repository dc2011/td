#ifndef EFFECT_H
#define EFFECT_H

#include <QString>

#include "../physics/PhysicsComponent.h"
#include "Unit.h"

namespace td {

class Effect : public GameObject {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kEffect;
    }

public:
    Effect(Unit* unit);
    void apply();
    size_t getDuration();
    void setDuration(size_t);

private:
    Unit *unit_;
    size_t duration_;
};

} /* end namespace td */

#endif // EFFECT_H
