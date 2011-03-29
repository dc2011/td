#include "EffectTypes.h"
#include "../util/defines.h"

namespace td {

NPCPlayerEffect::NPCPlayerEffect(Unit* unit)
        : Effect(unit, NPC_PLAYER_TIME) {
    velocityChangeValue_ = QVector2D(0,0);       
}

void NPCPlayerEffect::apply() {
    unit_->setVelocity(velocityChangeValue_);
}

ArrowEffect::ArrowEffect(Unit* unit)
        : Effect(unit, ARROW_TIME) {
    velocityChangeValue_ = QVector2D(0,0);       
    healthChangeValue_ = -25;
}

void ArrowEffect::apply() {
    unit_->setVelocity(velocityChangeValue_);
    unit_->setHealth(unit_->getHealth() + healthChangeValue_);
}

} /* end namespace td */

