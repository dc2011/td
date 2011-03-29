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

} /* end namespace td */

