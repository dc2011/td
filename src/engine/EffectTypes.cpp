#include "EffectTypes.h"
#include "../util/defines.h"
#include "NPC.h"
#include "Player.h"

namespace td {

NPCPlayerEffect::NPCPlayerEffect(Unit* unit)

        : Effect(unit, NPC_PLAYER_TIME, EFFECT_NPCPLAYER, TRUE) {
    velocityChangeValue_ = 0;
}

void NPCPlayerEffect::apply() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(velocityChangeValue_);
}

ArrowEffect::ArrowEffect(Unit* unit)
        : Effect(unit, ARROW_TIME, EFFECT_ARROW, TRUE) {
    velocityChangeValue_ = 0;
    healthChangeValue_ = -25;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
        + healthChangeValue_);
}

void ArrowEffect::apply() {
    unit_->setVelocity(velocityChangeValue_);
}

PlayerTerrainEffect::PlayerTerrainEffect(Unit* unit)
    : Effect(unit, NO_TIME, EFFECT_TERRAIN, FALSE) {
    velocityChangeValue_ = 0;

}

void PlayerTerrainEffect::apply() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(velocityChangeValue_);
}


NPCTarEffect::NPCTarEffect(Unit* unit)
    : Effect(unit, TAR_TIME, EFFECT_TAR, TRUE) {
    velocityChangeValue_ = 0;
    healthChangeValue_ = -25;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
                                + healthChangeValue_);
}

void NPCTarEffect::apply() {
    velocityChangeValue_ = 0;
}

NPCBurnEffect::NPCBurnEffect(Unit* unit):Effect(unit, BURN_TIME) {
    healthChangeValue_ = -5;
}

void NPCBurnEffect::apply() {
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

} /* end namespace td */

