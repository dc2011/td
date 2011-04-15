#include "EffectTypes.h"
#include "../util/defines.h"
#include "NPC.h"
#include "Player.h"
#include "Tile.h"

namespace td {

NPCPlayerEffect::NPCPlayerEffect(Unit* unit): Effect(unit, EFFECT_NPCPLAYER, NPC_PLAYER_TIME) {
    oldVelocity_ = PLAYER_MAX_V;
    velocityChangeValue_ = oldVelocity_ / 5;
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(velocityChangeValue_);
}

NPCPlayerEffect::~NPCPlayerEffect() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(oldVelocity_);
}

void NPCPlayerEffect::apply() {}

ArrowEffect::ArrowEffect(Unit* unit)
        : Effect(unit, EFFECT_ARROW, ARROW_TIME) {    

    healthChangeValue_ = -25;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void ArrowEffect::apply() {}

CannonEffect::CannonEffect(Unit* unit)
        : Effect(unit, EFFECT_CANNON, CANNON_TIME, TRUE){
    healthChangeValue_ = -75;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void CannonEffect::apply() {}

FlakEffect::FlakEffect(Unit* unit)
        : Effect(unit, EFFECT_FLAK, FLAK_TIME, TRUE){
    healthChangeValue_ = -10;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void FlakEffect::apply(){}

PlayerTerrainSlowEffect::PlayerTerrainSlowEffect(Unit* unit)
    : Effect(unit, EFFECT_SLOW, NO_TIME) {
    oldVelocity_ = PLAYER_MAX_V;
    velocityChangeValue_ = oldVelocity_ / 5;
}

PlayerTerrainSlowEffect::~PlayerTerrainSlowEffect() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(oldVelocity_);
}

void PlayerTerrainSlowEffect::apply() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(velocityChangeValue_);
    if((((Player*)unit_)->tileThatPlayerIsOn_)->getTileEffect() == Tile::NONE
            || (((Player*)unit_)->tileThatPlayerIsOn_)->getTileEffect() == Tile::FAST) {
        emit effectFinished(this);
    }
}

PlayerTerrainFastEffect::PlayerTerrainFastEffect(Unit* unit)
    : Effect(unit, EFFECT_FAST, NO_TIME) {
    oldVelocity_ = PLAYER_MAX_V;
    velocityChangeValue_ = oldVelocity_*2;
}

PlayerTerrainFastEffect::~PlayerTerrainFastEffect() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(oldVelocity_);
}

void PlayerTerrainFastEffect::apply() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(velocityChangeValue_);
    if((((Player*)unit_)->tileThatPlayerIsOn_)->getTileEffect() == Tile::NONE
            || (((Player*)unit_)->tileThatPlayerIsOn_)->getTileEffect() == Tile::SLOW) {
        emit effectFinished(this);
    }
}

NPCTarEffect::NPCTarEffect(Unit* unit)
    : Effect(unit, EFFECT_TAR, TAR_TIME) {
    oldVelocity_ = ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))->getMaxVelocity();

    velocityChangeValue_ = oldVelocity_ / 2;
    healthChangeValue_ = -15;

    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
                                + healthChangeValue_);
    ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(velocityChangeValue_);

}

NPCTarEffect::~NPCTarEffect() {
    ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(oldVelocity_);
}

void NPCTarEffect::apply() {}

FireEffect::FireEffect(Unit* unit)
        : Effect(unit, EFFECT_FIRE, FIRE_TIME, TRUE){
    healthChangeValue_ = -10;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void FireEffect::apply(){}

NPCBurnEffect::NPCBurnEffect(Unit* unit):Effect(unit, EFFECT_BURN, BURN_TIME) {
    healthChangeValue_ = -5;
    count_ = 15;
}

void NPCBurnEffect::apply() {
    if(count_ % 15 == 0){
        ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
    }
    count_++;
}

} /* end namespace td */

