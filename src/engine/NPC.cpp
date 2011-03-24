#include "NPC.h"
#ifndef SERVER
#include "CDriver.h"
#endif
//#ifdef SERVER
//#include "SDriver.h"
//#endif
namespace td {

NPC::NPC(QObject* parent) : Unit(parent) {
    QVector2D force(0, 0);
    this->setForce(force);
    this->setVelocity(force);
    this->setHeight(90);
    this->setWidth(30);
    pos_.setX(50);
    pos_.setY(50);
    health_ = 1;
    #ifndef SERVER
    if(CDriver::instance()->isSinglePlayer()) {
        connect(this, SIGNAL(dead(int)), CDriver::instance(), SLOT(deadNPC(int)));
    }
    #endif
    //#ifdef SERVER
    //connect(this, SIGNAL(dead(int)), SDriver::instance(), SLOT(deadNPC(int)));
    // #endif
   
}

NPC::~NPC() {
    emit signalNPCDied();
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

size_t NPC::getMaxHealth() {
    return maxHealth_;
}

void NPC::setMaxHealth(size_t maxHealth) {
    maxHealth_ = maxHealth;
}

void NPC::initComponents() {
#ifndef SERVER
    static int flipFloper = 0;
    ++flipFloper = flipFloper % 2;
    GraphicsComponent* graphics = new NPCGraphicsComponent(flipFloper + 1);
    this->setGraphicsComponent(graphics);
#endif

    PhysicsComponent* physics = new NPCPhysicsComponent();
    NPCInputComponent* input = new NPCInputComponent();

    input->setParent(this);
    this->setInputComponent(input);
    this->setPhysicsComponent(physics);
}
void NPC::isDead() {
    if(health_ == 0) {
        emit dead(this->getID());
    }
}
void NPC::update() {
#ifndef SERVER
    CDriver::updateServer(this);
#endif
    input_->update();
    physics_->update(this);
    graphics_->update(this);
    this->isDead();
}

} /* end namespace td */
