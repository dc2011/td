#include "NPC.h"
#ifndef SERVER
#include "CDriver.h"
#endif
#include "../input/NPCInputComponentTypes.h"
#include "../physics/NPCPhysicsComponentTypes.h"
#include "../graphics/NPCGraphicsComponentTypes.h"
#include "../util/defines.h"
//#ifdef SERVER
//#include "SDriver.h"
//#endif
namespace td {

NPC::NPC() {
    QVector2D force(0, 0);
    this->setForce(force);
    this->setVelocity(force);
    this->setHeight(90);
    this->setWidth(30);
    pos_.setX(50);
    pos_.setY(50);
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
    /*
    static int flipFloper = 0;
    ++flipFloper = flipFloper % 2;
    PhysicsComponent* physics = new NPCPhysicsComponent(0.2, 0.25, 2);
    GraphicsComponent* graphics = new NPCGraphicsComponent(flipFloper + 1);
    NPCInputComponent* input = new NPCInputComponent();

    input->setParent(this);
    this->setInputComponent(input);
    this->setPhysicsComponent(physics);
    this->setGraphicsComponent(graphics);
    */
    NPCInputComponent* input;

    switch(type_) {
        case NPC_NORM:
            health_ = 100;
            input = new NormNPCInputComponent();
            input->setParent(this);
            setPhysicsComponent(new NormNPCPhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new NormNPCGraphicsComponent());
#endif
            setInputComponent(input);
            break;
        case NPC_SLOW:
            health_ = 200;
            input = new SlowNPCInputComponent();
            input->setParent(this);
            setPhysicsComponent(new SlowNPCPhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new SlowNPCGraphicsComponent());
#endif
            setInputComponent(input);
            break;
        case NPC_FAST:
            health_ = 50;
            input = new FastNPCInputComponent();
            input->setParent(this);
            setPhysicsComponent(new FastNPCPhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new FastNPCGraphicsComponent());
#endif
            setInputComponent(input);
            break;
        case NPC_FLY:
            health_ = 100;
            input = new FlyNPCInputComponent();
            input->setParent(this);
            setPhysicsComponent(new FlyNPCPhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new FlyNPCGraphicsComponent());
#endif
            setInputComponent(input);
            break;
        case NPC_BOSS:
            health_ = 300;
            input = new BossNPCInputComponent();
            input->setParent(this);
            setPhysicsComponent(new BossNPCPhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new BossNPCGraphicsComponent());
#endif
            setInputComponent(input);
            break;

    }
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
