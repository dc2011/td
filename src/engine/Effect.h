#ifndef EFFECT_H
#define EFFECT_H

#include <QString>
#include <QTimer>
#include <QVector>

#include "GameObject.h"
#include "Unit.h"
#include "../physics/PhysicsComponent.h"

// effect types for operator==
#define EFFECT_NONE         0
#define EFFECT_NPCPLAYER    1
#define EFFECT_TERRAIN      2
#define EFFECT_ARROW        3
#define EFFECT_TAR          4

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

    Effect(const Effect& e);
    Effect(Unit* unit, int duration, uint type, bool timerEnabled = true);
    ~Effect();

    Effect& operator=(const Effect &rhs);
    bool operator==(const Effect &e) const;
    bool operator!=(const Effect &e) const;

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
    virtual void apply();

    void setDuration(size_t duration);
    size_t getDuration();

    void setVelocityChangeValue(QVector2D velocity);
    QVector2D getVelocityChangeValue();

    void setHealthChangeValue(int healthChange);
    int getHealthChangeValue();

    /**
     * Returns the type of Effect.
     *
     * @author Marcel Vangrootheest
     * @return The type of Effect
     */
    uint getType() {
        return type_;
    }

private:
    void countdown();

public slots:
    void update();

    /**
     * Stops applying the effect if the correct type.
     * Connected to stopEffect(uint) in Unit.
     *
     * @author Marcel Vangrootheest
     * @param type The type of Effect.
     */
    void effectStop(uint type);

signals:
    void effectFinished(Effect* effect);

protected:
    Unit* unit_;
    //EffectType type_;
    size_t duration_;
    int healthChangeValue_;
    QVector2D velocityChangeValue_;
    uint type_;
    bool timerEnabled_;
    bool applyEnabled_;
};

} /* end namespace td */

#endif // EFFECT_H
