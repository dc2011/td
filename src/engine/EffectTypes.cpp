#include "EffectTypes.h"
#include "../util/defines.h"
#include "NPC.h"
#include "Player.h"
#include "Tile.h"

namespace td {

NPCPlayerEffect::NPCPlayerEffect(Unit* unit)
    : Effect(unit, EFFECT_NPCPLAYER, NPC_PLAYER_TIME) {
    oldVelocity_ = ((PlayerPhysicsComponent*)unit->getPhysicsComponent())
        ->getMaxVelocity();
    velocityChangeValue_ = oldVelocity_ / 5;
    ((PlayerPhysicsComponent*)unit_->getPhysicsComponent())
        ->setMaxVelocity(velocityChangeValue_);
}

NPCPlayerEffect::~NPCPlayerEffect() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(oldVelocity_);
}

void NPCPlayerEffect::apply() {}

UpgradeNPCPlayerEffect::UpgradeNPCPlayerEffect(Unit* unit)
    : Effect(unit, EFFECT_NPCPLAYER, NPC_PLAYER_TIME_UPGRADE) {
    oldVelocity_ = ((PlayerPhysicsComponent*)unit->getPhysicsComponent())->getMaxVelocity();
    velocityChangeValue_ = oldVelocity_ / 5;
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(velocityChangeValue_);
}

UpgradeNPCPlayerEffect::~UpgradeNPCPlayerEffect() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(oldVelocity_);
}

void UpgradeNPCPlayerEffect::apply() {}

ArrowEffect::ArrowEffect(Unit* unit)
        : Effect(unit, EFFECT_ARROW, ARROW_TIME) {    
    if (unit_ == NULL) {
        return;
    }

    if (((NPC*)unit_)->getType() == NPC_ARM) {
        healthChangeValue_ = ARROW_ARM_DMG;
    } else {
        healthChangeValue_ = ARROW_DMG;
    }
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void ArrowEffect::apply() {}

ArrowEffectL2::ArrowEffectL2(Unit* unit)
        : Effect(unit, EFFECT_ARROW, ARROW_TIME) {    

    if (((NPC*)unit_)->getType() == NPC_ARM) {
        healthChangeValue_ = ARROW_ARM_DMG_2;
    } else {
        healthChangeValue_ = ARROW_DMG_2;
    }
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void ArrowEffectL2::apply() {}

ArrowEffectL3::ArrowEffectL3(Unit* unit)
        : Effect(unit, EFFECT_ARROW, ARROW_TIME) {    

    if (((NPC*)unit_)->getType() == NPC_ARM) {
        healthChangeValue_ = ARROW_ARM_DMG_3;
    } else {
        healthChangeValue_ = ARROW_DMG_3;
    }
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void ArrowEffectL3::apply() {}

ArrowEffectL4::ArrowEffectL4(Unit* unit)
        : Effect(unit, EFFECT_ARROW, ARROW_TIME) {    

    if (((NPC*)unit_)->getType() == NPC_ARM) {
        healthChangeValue_ = ARROW_ARM_DMG_4;
    } else {
        healthChangeValue_ = ARROW_DMG_4;
    }
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void ArrowEffectL4::apply() {}

ArrowEffectL5::ArrowEffectL5(Unit* unit)
        : Effect(unit, EFFECT_ARROW, ARROW_TIME) {    

    if (((NPC*)unit_)->getType() == NPC_ARM) {
        healthChangeValue_ = ARROW_ARM_DMG_5;
    } else {
        healthChangeValue_ = ARROW_DMG_5;
    }
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void ArrowEffectL5::apply() {}

CannonEffect::CannonEffect(Unit* unit)
        : Effect(unit, EFFECT_CANNON, CANNON_TIME){
    healthChangeValue_ = CANNON_DMG;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void CannonEffect::apply() {}

CannonEffectL2::CannonEffectL2(Unit* unit)
        : Effect(unit, EFFECT_CANNON, CANNON_TIME){
    healthChangeValue_ = CANNON_DMG_2;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void CannonEffectL2::apply() {}

CannonEffectL3::CannonEffectL3(Unit* unit)
        : Effect(unit, EFFECT_CANNON, CANNON_TIME){
    healthChangeValue_ = CANNON_DMG_3;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void CannonEffectL3::apply() {}

CannonEffectL4::CannonEffectL4(Unit* unit)
        : Effect(unit, EFFECT_CANNON, CANNON_TIME){
    healthChangeValue_ = CANNON_DMG_4;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void CannonEffectL4::apply() {}

CannonEffectL5::CannonEffectL5(Unit* unit)
        : Effect(unit, EFFECT_CANNON, CANNON_TIME){
    healthChangeValue_ = CANNON_DMG_5;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void CannonEffectL5::apply() {}

FlakEffect::FlakEffect(Unit* unit)
        : Effect(unit, EFFECT_FLAK, FLAK_TIME, TRUE){
    healthChangeValue_ = FLAK_DMG;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void FlakEffect::apply(){}

FlakEffectL2::FlakEffectL2(Unit* unit)
        : Effect(unit, EFFECT_FLAK, FLAK_TIME, TRUE){
    healthChangeValue_ = FLAK_DMG_2;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void FlakEffectL2::apply(){}

FlakEffectL3::FlakEffectL3(Unit* unit)
        : Effect(unit, EFFECT_FLAK, FLAK_TIME, TRUE){
    healthChangeValue_ = FLAK_DMG_3;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void FlakEffectL3::apply(){}

FlakEffectL4::FlakEffectL4(Unit* unit)
        : Effect(unit, EFFECT_FLAK, FLAK_TIME, TRUE){
    healthChangeValue_ = FLAK_DMG_4;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void FlakEffectL4::apply(){}

FlakEffectL5::FlakEffectL5(Unit* unit)
        : Effect(unit, EFFECT_FLAK, FLAK_TIME, TRUE){
    healthChangeValue_ = FLAK_DMG_5;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void FlakEffectL5::apply(){}

PlayerTerrainSlowEffect::PlayerTerrainSlowEffect(Unit* unit)
    : Effect(unit, EFFECT_SLOW, NO_TIME) {
    oldVelocity_ = ((PlayerPhysicsComponent*)unit->getPhysicsComponent())->getMaxVelocity();
    velocityChangeValue_ = oldVelocity_ / 2;
}

PlayerTerrainSlowEffect::~PlayerTerrainSlowEffect() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(oldVelocity_);
}

void PlayerTerrainSlowEffect::apply() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(velocityChangeValue_);
    if((((Player*)unit_)->tileThatPlayerIsOn_)->getTileEffect() == Tile::NONE
            || (((Player*)unit_)->tileThatPlayerIsOn_)->getTileEffect()
            == Tile::FAST) {
        emit effectFinished(this);
    }
}

PlayerTerrainFastEffect::PlayerTerrainFastEffect(Unit* unit)
    : Effect(unit, EFFECT_FAST, NO_TIME) {
    oldVelocity_ = ((PlayerPhysicsComponent*)unit->getPhysicsComponent())->getMaxVelocity();
    velocityChangeValue_ = oldVelocity_ * 1.75;
}

PlayerTerrainFastEffect::~PlayerTerrainFastEffect() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(oldVelocity_);
}

void PlayerTerrainFastEffect::apply() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(velocityChangeValue_);
    if((((Player*)unit_)->tileThatPlayerIsOn_)->getTileEffect() == Tile::NONE
            || (((Player*)unit_)->tileThatPlayerIsOn_)->getTileEffect()
            == Tile::SLOW) {
        emit effectFinished(this);
    }
}

NPCTarEffect::NPCTarEffect(Unit* unit)
    : Effect(unit, EFFECT_TAR, TAR_TIME) {
    oldVelocity_ = ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->getMaxVelocity();

    velocityChangeValue_ = oldVelocity_ / 2;
    healthChangeValue_ = TAR_DMG;

    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
                                + healthChangeValue_);
    ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(velocityChangeValue_);

}

NPCTarEffect::~NPCTarEffect() {
    ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(oldVelocity_);
}

void NPCTarEffect::apply() {}

NPCTarEffectL2::NPCTarEffectL2(Unit* unit)
    : Effect(unit, EFFECT_TAR, TAR_TIME_2) {
    oldVelocity_ = ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->getMaxVelocity();

    velocityChangeValue_ = oldVelocity_ / 2;
    healthChangeValue_ = TAR_DMG_2;

    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
                                + healthChangeValue_);
    ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(velocityChangeValue_);

}

NPCTarEffectL2::~NPCTarEffectL2() {
    ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(oldVelocity_);
}

void NPCTarEffectL2::apply() {}

NPCTarEffectL3::NPCTarEffectL3(Unit* unit)
    : Effect(unit, EFFECT_TAR, TAR_TIME_3) {
    oldVelocity_ = ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->getMaxVelocity();

    velocityChangeValue_ = oldVelocity_ / 2;
    healthChangeValue_ = TAR_DMG_3;

    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
                                + healthChangeValue_);
    ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(velocityChangeValue_);

}

NPCTarEffectL3::~NPCTarEffectL3() {
    ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(oldVelocity_);
}

void NPCTarEffectL3::apply() {}

NPCTarEffectL4::NPCTarEffectL4(Unit* unit)
    : Effect(unit, EFFECT_TAR, TAR_TIME_4) {
    oldVelocity_ = ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->getMaxVelocity();

    velocityChangeValue_ = oldVelocity_ / 2;
    healthChangeValue_ = TAR_DMG_4;

    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
                                + healthChangeValue_);
    ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(velocityChangeValue_);

}

NPCTarEffectL4::~NPCTarEffectL4() {
    ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(oldVelocity_);
}

void NPCTarEffectL4::apply() {}

NPCTarEffectL5::NPCTarEffectL5(Unit* unit)
    : Effect(unit, EFFECT_TAR, TAR_TIME_5) {
    oldVelocity_ = ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->getMaxVelocity();

    velocityChangeValue_ = oldVelocity_ / 2;
    healthChangeValue_ = TAR_DMG_5;

    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
                                + healthChangeValue_);
    ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(velocityChangeValue_);

}

NPCTarEffectL5::~NPCTarEffectL5() {
    ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))
        ->setMaxVelocity(oldVelocity_);
}

void NPCTarEffectL5::apply() {}

FireEffect::FireEffect(Unit* unit)
        : Effect(unit, EFFECT_FIRE, FIRE_TIME){
    healthChangeValue_ = FIRE_DMG;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void FireEffect::apply(){}

NPCBurnEffect::NPCBurnEffect(Unit* unit):Effect(unit, EFFECT_BURN, BURN_TIME) {
    healthChangeValue_ = BURN_DMG;
    count_ = 15;
}

void NPCBurnEffect::apply() {
    if(count_ % 15 == 0){
        ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
            + healthChangeValue_);
    }
    count_++;
}

FireEffectL2::FireEffectL2(Unit* unit)
        : Effect(unit, EFFECT_FIRE, FIRE_TIME){
    healthChangeValue_ = FIRE_DMG_2;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void FireEffectL2::apply(){}

NPCBurnEffectL2::NPCBurnEffectL2(Unit* unit)
    :Effect(unit, EFFECT_BURN, BURN_TIME_2) {
    healthChangeValue_ = BURN_DMG_2;
    count_ = 15;
}

void NPCBurnEffectL2::apply() {
    if(count_ % 15 == 0){
        ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
            + healthChangeValue_);
    }
    count_++;
}

FireEffectL3::FireEffectL3(Unit* unit)
        : Effect(unit, EFFECT_FIRE, FIRE_TIME){
    healthChangeValue_ = FIRE_DMG_3;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void FireEffectL3::apply(){}

NPCBurnEffectL3::NPCBurnEffectL3(Unit* unit)
    :Effect(unit, EFFECT_BURN, BURN_TIME_3) {
    healthChangeValue_ = BURN_DMG_3;
    count_ = 15;
}

void NPCBurnEffectL3::apply() {
    if(count_ % 15 == 0){
        ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
            + healthChangeValue_);
    }
    count_++;
}

FireEffectL4::FireEffectL4(Unit* unit)
        : Effect(unit, EFFECT_FIRE, FIRE_TIME){
    healthChangeValue_ = FIRE_DMG_4;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void FireEffectL4::apply(){}

NPCBurnEffectL4::NPCBurnEffectL4(Unit* unit)
    :Effect(unit, EFFECT_BURN, BURN_TIME_4) {
    healthChangeValue_ = BURN_DMG_4;
    count_ = 15;
}

void NPCBurnEffectL4::apply() {
    if(count_ % 15 == 0){
        ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
            + healthChangeValue_);
    }
    count_++;
}

FireEffectL5::FireEffectL5(Unit* unit)
        : Effect(unit, EFFECT_FIRE, FIRE_TIME){
    healthChangeValue_ = FIRE_DMG_5;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

void FireEffectL5::apply(){}

NPCBurnEffectL5::NPCBurnEffectL5(Unit* unit)
    :Effect(unit, EFFECT_BURN, BURN_TIME_5) {
    healthChangeValue_ = BURN_DMG_5;
    count_ = 15;
}

void NPCBurnEffectL5::apply() {
    if(count_ % 15 == 0){
        ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
            + healthChangeValue_);
    }
    count_++;
}

} /* end namespace td */

