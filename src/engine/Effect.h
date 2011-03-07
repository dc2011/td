#ifndef EFFECT_H
#define EFFECT_H

#include <QString>
#include <QTimer>

#include "GameObject.h"
#include "../physics/PhysicsComponent.h"

namespace td {

class Effect : public GameObject {
    Q_OBJECT

    /**
     * List of effect types.
     *
     * @author Pan K.
     */
    enum EffectType{
        healthChange, damageChange, speedChange, directionChange, destroy
    };

public:
    Effect(GameObject* unit, EffectType type);
    ~Effect();

    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kEffect;
    }

    /**
     * Apply effect to the unit base on effectType. If the
     * duration is specified, the effect will repeatly apply
     * at speed per second (speed/sec).
     * If the duration is not set, the effect is applied once.
     *
     * @author Pan K.
     * @param duration Specify duration in msec.
     * @param speed Specify speed/sec
     */
    void apply(size_t duration = 0, size_t speed = 0);

private:
    GameObject *unit_;
    EffectType type_;
};

} /* end namespace td */

#endif // EFFECT_H
