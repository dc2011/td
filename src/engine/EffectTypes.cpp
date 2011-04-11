#include "EffectTypes.h"
#include "../util/defines.h"
#include "NPC.h"

namespace td {

NPCPlayerEffect::NPCPlayerEffect(Unit* unit)
        : Effect(unit, NPC_PLAYER_TIME, EFFECT_NPCPLAYER, TRUE) {
    velocityChangeValue_ = QVector2D(0,0);       
}

void NPCPlayerEffect::apply() {
    unit_->setVelocity(velocityChangeValue_);
}

ArrowEffect::ArrowEffect(Unit* unit)
        : Effect(unit, ARROW_TIME, EFFECT_ARROW, TRUE) {
    velocityChangeValue_ = QVector2D(0,0);       
    healthChangeValue_ = -25;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
        + healthChangeValue_);
}

void ArrowEffect::apply() {
    unit_->setVelocity(velocityChangeValue_);
}

PlayerTerrainEffect::PlayerTerrainEffect(Unit* unit)
    : Effect(unit, NO_TIME, EFFECT_TERRAIN, FALSE) {
    velocityChangeValue_ = QVector2D(0,0);
}

void PlayerTerrainEffect::apply() {
    unit_->setVelocity(velocityChangeValue_);
}

NPCTarEffect::NPCTarEffect(Unit* unit)
    : Effect(unit, TAR_TIME, EFFECT_TAR, TRUE) {
    velocityChangeValue_ = QVector2D(0,0);
    healthChangeValue_ = -25;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
                                + healthChangeValue_);
}

void NPCTarEffect::apply() {
    velocityChangeValue_ = QVector2D(0,0);
}

} /* end namespace td */

