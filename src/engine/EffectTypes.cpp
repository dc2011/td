#include "EffectTypes.h"
#include "../util/defines.h"
#include "NPC.h"
#include "Player.h"

namespace td {

NPCPlayerEffect::NPCPlayerEffect(Unit* unit)
        : Effect(unit, NPC_PLAYER_TIME) {
    setOldVelocity(((PlayerPhysicsComponent*)(getUnit()->getPhysicsComponent()))->getMaxVelocity());
    velocityChangeValue_ = 0;       
}

void NPCPlayerEffect::apply() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(velocityChangeValue_);
}
void NPCPlayerEffect::countdown() {
    Effect::countdown();
    if(getDuration() <= 0) {
        ((PlayerPhysicsComponent*)(getUnit()->getPhysicsComponent()))->setMaxVelocity(oldVelocity_);
    }
}

ArrowEffect::ArrowEffect(Unit* unit)
        : Effect(unit, ARROW_TIME) {    
    healthChangeValue_ = -25;
}

void ArrowEffect::apply() {
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

PlayerTerrainEffect::PlayerTerrainEffect(Unit* unit):Effect(unit, NO_TIME) {
    velocityChangeValue_ = 0;
}

void PlayerTerrainEffect::apply() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(velocityChangeValue_);
}
void PlayerTerrainEffect::countdown() {
    Effect::countdown();
    if(getDuration() <= 0) {
        ((PlayerPhysicsComponent*)(getUnit()->getPhysicsComponent()))->setMaxVelocity(oldVelocity_);
    }
}

NPCTarEffect::NPCTarEffect(Unit* unit):Effect(unit, TAR_TIME) {
    velocityChangeValue_ = 0;
    healthChangeValue_ = -25;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void NPCTarEffect::apply() {
    velocityChangeValue_ = 0;
}
void NPCTarEffect::countdown() {
    Effect::countdown();
    if(getDuration() <= 0) {
        ((NPCPhysicsComponent*)(getUnit()->getPhysicsComponent()))->setMaxVelocity(oldVelocity_);
    }
}

NPCBurnEffect::NPCBurnEffect(Unit* unit):Effect(unit, BURN_TIME) {
    healthChangeValue_ = -5;
}

void NPCBurnEffect::apply() {
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

} /* end namespace td */

