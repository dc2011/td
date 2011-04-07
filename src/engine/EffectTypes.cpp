#include "EffectTypes.h"
#include "../util/defines.h"
#include "NPC.h"

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
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

PlayerTerrainEffect::PlayerTerrainEffect(Unit* unit):Effect(unit, NO_TIME) {
    velocityChangeValue_ = QVector2D(0,0);
}

void PlayerTerrainEffect::apply() {
    unit_->setVelocity(velocityChangeValue_);
}

NPCTarEffect::NPCTarEffect(Unit* unit):Effect(unit, TAR_TIME) {
    velocityChangeValue_ = QVector2D(0,0);
    healthChangeValue_ = -25;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void NPCTarEffect::apply() {
    velocityChangeValue_ = QVector2D(0,0);
}

NPCBurnEffect::NPCBurnEffect(Unit* unit):Effect(unit, BURN_TIME) {
    healthChangeValue_ = -5;
}

void NPCBurnEffect::apply() {
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

} /* end namespace td */

