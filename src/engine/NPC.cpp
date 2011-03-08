#include "NPC.h"
#include "CDriver.h"
namespace td {

NPC::NPC() {
    QVector2D force(0, 0);
    this->setForce(force);
    this->setVelocity(force);
    pos_.setX(50);
    pos_.setY(50);
}

size_t NPC::getHealth() {
    return health_;
}

void NPC::setHealth(size_t health){
    health_ = health;
}

size_t NPC::getDamage() {
    return damage_;
}

void NPC::setDamage(size_t damage) {
    damage_ = damage;
}

void NPC::update() {
    input_->update();
    physics_->update(this);
    graphics_->update(this);
    CDriver::updateServer(this);
}

} /* end namespace td */
