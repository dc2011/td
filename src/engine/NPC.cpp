#include "NPC.h"
#ifndef SERVER
#include "CDriver.h"
#endif
namespace td {

NPC::NPC() {
    QVector2D force(0, 0);
    this->setForce(force);
    this->setVelocity(force);
    this->setHeight(90);
    this->setWidth(30);
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

void NPC::initComponents() {
    static int flipFloper = 0;
    ++flipFloper = flipFloper % 2;
    PhysicsComponent* physics = new NPCPhysicsComponent();
    GraphicsComponent* graphics = new NPCGraphicsComponent(flipFloper + 1);
    NPCInputComponent* input = new NPCInputComponent();

    input->setParent(this);
    this->setInputComponent(input);
    this->setPhysicsComponent(physics);
    this->setGraphicsComponent(graphics);
}

void NPC::update() {
#ifndef SERVER
    CDriver::updateServer(this);
#endif
    input_->update();
    physics_->update(this);
    graphics_->update(this);
}

} /* end namespace td */
