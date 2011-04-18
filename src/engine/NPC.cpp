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
    this->getDriver()->getGameMap()->removeUnit(getPos().x(), getPos().y(), this);
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
        maxHealth_ = health_ = NPC_NORM_HP;
        height_ = NPC_NORM_HEIGHT;
        width_ = NPC_NORM_WIDTH;
        input = new NormNPCInputComponent();
        input->setParent(this);
        setPhysicsComponent(new NormNPCPhysicsComponent());
#ifndef SERVER
        setGraphicsComponent(new NormNPCGraphicsComponent());
#endif
        setInputComponent(input);
        break;
    case NPC_SLOW:
        maxHealth_ = health_ = NPC_SLOW_HP;
        height_ = NPC_SLOW_HEIGHT;
        width_ = NPC_SLOW_WIDTH;
        input = new SlowNPCInputComponent();
        input->setParent(this);
        setPhysicsComponent(new SlowNPCPhysicsComponent());
#ifndef SERVER
        setGraphicsComponent(new SlowNPCGraphicsComponent());
#endif
        setInputComponent(input);
        break;
    case NPC_ARM:
        maxHealth_ = health_ = NPC_ARM_HP;
        height_ = NPC_ARM_HEIGHT;
        width_ = NPC_ARM_WIDTH;
        input = new ArmNPCInputComponent();
        input->setParent(this);
        setPhysicsComponent(new ArmNPCPhysicsComponent());
#ifndef SERVER
        setGraphicsComponent(new ArmNPCGraphicsComponent());
#endif
        setInputComponent(input);
        break;
    case NPC_FAST:
        maxHealth_ = health_ = NPC_FAST_HP;
        height_ = NPC_FAST_HEIGHT;
        width_ = NPC_FAST_WIDTH;
        input = new FastNPCInputComponent();
        input->setParent(this);
        setPhysicsComponent(new FastNPCPhysicsComponent());
#ifndef SERVER
        setGraphicsComponent(new FastNPCGraphicsComponent());
#endif
        setInputComponent(input);
        break;
    case NPC_SWARM:
        maxHealth_ = health_ = NPC_SWARM_HP;
        height_ = NPC_SWARM_HEIGHT;
        width_ = NPC_SWARM_WIDTH;
        input = new SwarmNPCInputComponent();
        input->setParent(this);
        setPhysicsComponent(new SwarmNPCPhysicsComponent());
#ifndef SERVER
        setGraphicsComponent(new SwarmNPCGraphicsComponent());
#endif
        setInputComponent(input);
        break;
    case NPC_FLY:
        maxHealth_ = health_ = NPC_FLY_HP;
        height_ = NPC_FLY_HEIGHT;
        width_ = NPC_FLY_WIDTH;
        input = new FlyNPCInputComponent();
        input->setParent(this);
        setPhysicsComponent(new FlyNPCPhysicsComponent());
#ifndef SERVER
        setGraphicsComponent(new FlyNPCGraphicsComponent());
#endif
        setInputComponent(input);
        break;
    case NPC_BOSS:
        maxHealth_ = health_ = NPC_BOSS_HP;
        height_ = NPC_BOSS_HEIGHT;
        width_ = NPC_BOSS_WIDTH;
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
    if (effectType >= EFFECT_ARROW && effectType <= EFFECT_ARROW_5) {
        switch (effectType) {
            case EFFECT_ARROW:
                effect = new ArrowEffect(this);
                break;
            case EFFECT_ARROW_2:
                effect = new ArrowEffectL2(this);
                break;
            case EFFECT_ARROW_3:
                effect = new ArrowEffectL3(this);
                break;
            case EFFECT_ARROW_4:
                effect = new ArrowEffectL4(this);
                break;
            case EFFECT_ARROW_5:
                effect = new ArrowEffectL5(this);
                break;
        }
    } else if (effectType >= EFFECT_TAR && effectType <= EFFECT_TAR_5) {
        if (effects_.contains(EFFECT_TAR)) {
            deleteEffect(effects_.value(EFFECT_TAR));
        }
        switch (effectType) {
            case EFFECT_TAR:
                effect = new NPCTarEffect(this);
                break;
            case EFFECT_TAR_2:
                effect = new NPCTarEffectL2(this);
                break;
            case EFFECT_TAR_3:
                effect = new NPCTarEffectL3(this);
                break;
            case EFFECT_TAR_4:
                effect = new NPCTarEffectL4(this);
                break;
            case EFFECT_TAR_5:
                effect = new NPCTarEffectL5(this);
                break;
        }
    } else if (effectType >= EFFECT_FIRE && effectType <= EFFECT_FIRE_5) {
        switch (effectType) {
            case EFFECT_FIRE:
                if (effects_.contains(EFFECT_TAR)) {
                    deleteEffect(effects_.value(EFFECT_TAR));
                    if (effects_.contains(EFFECT_BURN)) {
                        deleteEffect(effects_.value(EFFECT_BURN));
                    }
                    effect = new NPCBurnEffect(this);
                    effects_.insert(effect->getType(), effect);
                }
                effect = new FireEffect(this);
                break;
            case EFFECT_FIRE_2:
                if (effects_.contains(EFFECT_TAR)) {
                    deleteEffect(effects_.value(EFFECT_TAR));
                    if (effects_.contains(EFFECT_BURN)) {
                        deleteEffect(effects_.value(EFFECT_BURN));
                    }
                    effect = new NPCBurnEffectL2(this);
                    effects_.insert(effect->getType(), effect);
                }
                effect = new FireEffectL2(this);
                break;
            case EFFECT_FIRE_3:
                if (effects_.contains(EFFECT_TAR)) {
                    deleteEffect(effects_.value(EFFECT_TAR));
                    if (effects_.contains(EFFECT_BURN)) {
                        deleteEffect(effects_.value(EFFECT_BURN));
                    }
                    effect = new NPCBurnEffectL3(this);
                    effects_.insert(effect->getType(), effect);
                }
                effect = new FireEffectL3(this);
                break;
            case EFFECT_FIRE_4:
                if (effects_.contains(EFFECT_TAR)) {
                    deleteEffect(effects_.value(EFFECT_TAR));
                    if (effects_.contains(EFFECT_BURN)) {
                        deleteEffect(effects_.value(EFFECT_BURN));
                    }
                    effect = new NPCBurnEffectL4(this);
                    effects_.insert(effect->getType(), effect);
                }
                effect = new FireEffectL4(this);
                break;
            case EFFECT_FIRE_5:
                if (effects_.contains(EFFECT_TAR)) {
                    deleteEffect(effects_.value(EFFECT_TAR));
                    if (effects_.contains(EFFECT_BURN)) {
                        deleteEffect(effects_.value(EFFECT_BURN));
                    }
                    effect = new NPCBurnEffectL5(this);
                    effects_.insert(effect->getType(), effect);
                }
                effect = new FireEffectL5(this);
                break;
        }
    } else if (effectType >= EFFECT_FLAK && effectType <= EFFECT_FLAK_5) {
        switch (effectType) {
            case EFFECT_FLAK:
                effect = new FlakEffect(this);
                break;
            case EFFECT_FLAK_2:
                effect = new FlakEffectL2(this);
                break;
            case EFFECT_FLAK_3:
                effect = new FlakEffectL3(this);
                break;
            case EFFECT_FLAK_4:
                effect = new FlakEffectL4(this);
                break;
            case EFFECT_FLAK_5:
                effect = new FlakEffectL5(this);
                break;
        }
    } else if (effectType >= EFFECT_CANNON && effectType <= EFFECT_CANNON_5) {
        switch (effectType) {
            case EFFECT_CANNON:
                effect = new CannonEffect(this);
                break;
            case EFFECT_CANNON_2:
                effect = new CannonEffectL2(this);
                break;
            case EFFECT_CANNON_3:
                effect = new CannonEffectL3(this);
                break;
            case EFFECT_CANNON_4:
                effect = new CannonEffectL4(this);
                break;
            case EFFECT_CANNON_5:
                effect = new CannonEffectL5(this);
                break;
        }
    }  else {
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
void NPC::setPos(float x, float y) {
    QPointF p;
    p.setX(x);
    p.setY(y);
    setPos(p);
}

void NPC::setPos(QPointF& p) {
    int x = getDriver()->getGameMap()->getWidthInTiles();
    int y = getDriver()->getGameMap()->getHeightInTiles();
    x = x * getDriver()->getGameMap()->getTMap()->tileWidth();
    y = y * getDriver()->getGameMap()->getTMap()->tileHeight();
    x-=20;
    y-=20;
    if(p.x() < 20) {
        p.setX(20);
    }
    if(p.y() < 20) {
        p.setY(20);
    }
    if(p.x() > x) {
        p.setX(x);
    }
    if(p.y() > y) {
        p.setY(y);
    }

    QPointF point;
    QVector<QPointF> points;
    QMatrix matrix = QMatrix();
    matrix.rotate(-getOrientation());
    // Determine if the NPC needs to update its tile position.
    changeTile(p);
    //set up Vector to construct bounding Polygon
    point = QPointF(-getWidth()/2, -getHeight( )/2) * matrix;
    point += p;
    points.append(point);
    point = QPointF(getWidth()/2, -getHeight()/2) * matrix;
    point += p;
    points.append(point);
    point = QPointF(getWidth()/2, getHeight()/2) * matrix;
    point += p;
    points.append(point);
    point = QPointF(-getWidth()/2, getHeight()/2) * matrix;
    point += p;
    points.append(point);
    point = QPointF(-getWidth()/2, -getHeight()/2) * matrix;
    point += p;
    points.append(point);

    setBounds(QPolygonF(points));

    pos_.setX(p.x());
    pos_.setY(p.y());
    setDirty(kPosition);
    //qDebug("Pos: (%.2f, %.2f)", (float) pos_.x(), (float) pos_.y());
}

} /* end namespace td */
