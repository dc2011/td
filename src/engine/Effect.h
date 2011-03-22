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
     */
    enum EffectType{ // This might need some changes
        healthChange, damageChange, speedChange, velocityChange, stunned
    };

    Effect(Unit* unit, EffectType type);
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
    void apply();

    void setDuration(size_t duration);
    size_t getDuration();

    void setVelocityChangeValue(QVector2D velocity);
    QVector2D getVelocityChangeValue();

    void setHealthChangeValue(int healthChange);
    int getHealthChangeValue();

public slots:
    void update();

signals:
    void effectFinished(Effect* effect);

private:
    Unit* unit_;
    EffectType type_;
    size_t duration_;
    int healthChangeValue_;
    QVector2D velocityChangeValue_;
};

} /* end namespace td */

#endif // EFFECT_H
