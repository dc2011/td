#include "NPC.h"
#include "NPCWave.h"
#include "Driver.h"
#include <QObject>
#include "../audio/SfxManager.h"

#ifndef SERVER
#    include "CDriver.h"
#    include "../graphics/EndingGraphicsComponentTypes.h"
#endif

namespace td {

NPC::NPC(QObject* parent) : Unit(parent), damage_(5), wave_(NULL) {
    QVector2D force(0, 0);
    this->setForce(force);
    this->setVelocity(force);
    pos_.setX(50);
    pos_.setY(50);

    connect(this, SIGNAL(dead(int)),
            parent, SLOT(destroyObject(int)), Qt::QueuedConnection);
}

NPC::~NPC() {
    // Delete all effects in the map
    foreach (Effect* e, effects_)
    {
        deleteEffect(e);
    }
    if (wave_ != NULL) {
        wave_->killChild(this);
    }
    emit signalNPCDied();
}

int NPC::getHealth() {
    return health_;
}

void NPC::setHealth(int health){
    health_ = health;
    setDirty(kHealth);
#ifndef SERVER
    // Make sure that we are only displaying health that exists...
    if (health_ > 0)
    {
        ((NPCGraphicsComponent*) graphics_)->showDamage();
    }
#endif
}

int NPC::getDamage() {
    return damage_;
}

void NPC::setDamage(int damage) {
    damage_ = damage;
}

int NPC::getMaxHealth() {
    return maxHealth_;
}

void NPC::setMaxHealth(int maxHealth) {
    maxHealth_ = maxHealth;
}

void NPC::networkRead(Stream* s) {
    Unit::networkRead(s);

    if (dirty_ & kType) {
        type_ = s->readInt();
    }

    if (dirty_ & kHealth) {
        health_ = s->readInt();
#ifndef SERVER
        if (graphics_ != NULL) {
            ((NPCGraphicsComponent*) graphics_)->showDamage();
        }
#endif
    }
}

void NPC::networkWrite(Stream* s) {
    Unit::networkWrite(s);

    if (dirty_ & kType) {
        s->writeInt(type_);
    }

    if (dirty_ & kHealth) {
        s->writeInt(health_);
    }
}

QVector2D NPC::getRandomVector() {
    float d = ((qrand() % 1000) / 21.0) + 50;
    float direction = (qrand() % 1000) - 500;
    QLineF normalVector = QLineF(QPointF(0, 0), velocity_.toPointF());

    normalVector = normalVector.normalVector();

    QVector2D v = QVector2D(normalVector.p2()) * direction;
    v.normalize();

    return (v * d);
}

void NPC::initComponents() {
    NPCInputComponent* input;

    switch(type_) {
    case NPC_NORM:
        maxHealth_ = health_ = 100;
        height_ = 90;
        width_ = 30;
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
        height_ = 30;
        width_ = 90;
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
        height_ = 30;
        width_ = 90;
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
        height_ = 30;
        width_ = 90;
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
        height_ = 30;
        width_ = 90;
        input = new BossNPCInputComponent();
        input->setParent(this);
        setPhysicsComponent(new BossNPCPhysicsComponent());
#ifndef SERVER
        setGraphicsComponent(new BossNPCGraphicsComponent());
#endif
        setInputComponent(input);
        break;
    }

#ifndef SERVER
    if (!((CDriver*)getDriver())->isSinglePlayer()) {
        delete getInputComponent();
        delete getPhysicsComponent();
        setInputComponent(NULL);
        setPhysicsComponent(NULL);
    }
#endif
}

void NPC::createEffect(int effectType)
{
    Effect* effect;

    // Create the effect
    switch (effectType) {
    case EFFECT_ARROW:
        effect = new ArrowEffect(this);
        break;
    case EFFECT_TAR:
        if (effects_.contains(EFFECT_TAR)) {
            deleteEffect(effects_.value(EFFECT_TAR));
        }
        effect = new NPCTarEffect(this);
        break;
    case EFFECT_FIRE:
        if (effects_.contains(EFFECT_TAR)) {
            deleteEffect(effects_.value(EFFECT_TAR));
            effect = new NPCBurnEffect(this);
            effects_.insert(effect->getType(), effect);
        }
        effect = new FireEffect(this);
        break;
    case EFFECT_FLAK:
        effect = new FlakEffect(this);
        break;
    case EFFECT_CANNON:
        effect = new CannonEffect(this);
        break;
    default:
        return;
    }
    effects_.insert(effect->getType(), effect);

}

void NPC::deleteEffect(Effect* effect)
{

    if (effects_.empty()) {
        // TODO: connect to a slot in projectile collisions for sfx
        //emit signalEmptyEffectList();
        return;
    }
    delete effects_.value(effect->getType());
    effects_.remove(effect->getType());

}

void NPC::isDead() {
    if(health_ <= 0) {
        //TODO NPC death sound/animation
#ifndef SERVER
        if (type_ == NPC_FLY) {
            new FlyingEndingGraphicsComponent(pos_);
        } else {
            new GenericNPCEndingGraphicsComponent(pos_);
        }
#endif
        emit signalDropResource(RESOURCE_GEM, pos_, getRandomVector());
        emit dead(this->getID());
    }
}

void NPC::update() {
    if (input_ != NULL) {
        input_->update();
    }
    if (physics_ != NULL) {
        physics_->update(this);
    }
    foreach(Effect* e, effects_) {
        e->update();
    }
    /*if (isDirty()) {
        getDriver()->updateRT(this);
    }*/

    if (graphics_ != NULL) {
        graphics_->update(this);
    }

    this->isDead();
}

} /* end namespace td */
