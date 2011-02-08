#ifndef EFFECT_H
#define EFFECT_H

#include <QString>

#include "PhysicsComponent.h"
#include "Unit.h"

class Effect : public GameObject {
    Q_OBJECT
public:
    Effect(Unit* unit);
    void apply();
    size_t getDuration();
    void setDuration(size_t);

private:
    Unit *unit_;
    size_t duration_;
};

#endif // EFFECT_H
