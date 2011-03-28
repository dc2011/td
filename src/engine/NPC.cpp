#include "NPC.h"
#include "Driver.h"
#include <QObject>

namespace td {

NPC::NPC(QObject* parent) : Unit(parent) {
    QVector2D force(0, 0);
    this->setForce(force);
    this->setVelocity(force);
    this->setHeight(90);
    this->setWidth(30);
    pos_.setX(50);
    pos_.setY(50);

    connect(this, SIGNAL(dead(int)),
            parent, SLOT(destroyObject(int)), Qt::QueuedConnection);
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
    this->setGraphicsComponent(graphics);

    PhysicsComponent* physics = new NPCPhysicsComponent();
    NPCInputComponent* input = new NPCInputComponent();

    input->setParent(this);
    this->setInputComponent(input);
    this->setPhysicsComponent(physics);
    this->setGraphicsComponent(graphics);
    */
    NPCInputComponent* input;

    switch(type_) {
        case NPC_NORM:
            maxHealth_ = health_ = 100;
            input = new NormNPCInputComponent();
            input->setParent(this);
            setPhysicsComponent(new NormNPCPhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new NormNPCGraphicsComponent());
#endif
            setInputComponent(input);
            break;
        case NPC_SLOW:
            maxHealth_ = health_ = 200;
            input = new SlowNPCInputComponent();
            input->setParent(this);
            setPhysicsComponent(new SlowNPCPhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new SlowNPCGraphicsComponent());
#endif
            setInputComponent(input);
            break;
        case NPC_FAST:
            maxHealth_ = health_ = 50;
            input = new FastNPCInputComponent();
            input->setParent(this);
            setPhysicsComponent(new FastNPCPhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new FastNPCGraphicsComponent());
#endif
            setInputComponent(input);
            break;
        case NPC_FLY:
            maxHealth_ = health_ = 100;
            input = new FlyNPCInputComponent();
            input->setParent(this);
            setPhysicsComponent(new FlyNPCPhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new FlyNPCGraphicsComponent());
#endif
            setInputComponent(input);
            break;
        case NPC_BOSS:
            maxHealth_ = health_ = 300;
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
    input_->update();
    physics_->update(this);

    if (isDirty()) {
        getDriver()->updateRT(this);
    }

    graphics_->update(this);
    this->isDead();
}

} /* end namespace td */
