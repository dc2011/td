#ifndef EFFECT_H
#define EFFECT_H

#include <QString>
#include <QTimer>
#include <QVector>

#include "GameObject.h"
#include "Unit.h"
#include "../physics/PhysicsComponent.h"

namespace td {

class Effect : public GameObject {
    Q_OBJECT

public:
        
    /**
     * List of effect types.
     *
     * @author Pan K.
     *
    enum EffectType{ // This might need some changes
        healthChange, damageChange, speedChange, velocityChange, stunned
    };
    */

    Effect(Unit* unit, int duration, bool timerEnabled = true);
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
     */
    virtual void apply() = 0;

    void setDuration(size_t duration);
    size_t getDuration();

    void setVelocityChangeValue(float velocity);
    float getVelocityChangeValue();

    void setHealthChangeValue(int healthChange);
    int getHealthChangeValue();

    /*inline getter*/
    Unit* getUnit() {
        return unit_;
    }
    /*inline setter*/
    void setOldVelocity(float oldVelocity) {
        oldVelocity_ = oldVelocity;
    }
    void countdown();

public slots:
    void update();

signals:
    void effectFinished(Effect* effect);

protected:
    Unit* unit_;
    //EffectType type_;
    size_t duration_;
    int healthChangeValue_;
    float velocityChangeValue_;
    float oldVelocity_;
    bool timerEnabled_;
};

} /* end namespace td */

#endif // EFFECT_H
