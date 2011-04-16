#include "Projectile.h"
#include "NPC.h"
#ifndef SERVER
#include "CDriver.h"
#endif
#include "../audio/SfxManager.h"
#include "EffectTypes.h"
#include "../util/defines.h"
#include "../input/ProjectileInputComponent.h"
#include "../input/ProjectileInputComponentTypes.h"
#include "../physics/ProjectilePhysicsComponentTypes.h"
#include "../graphics/ProjectileGraphicsComponentTypes.h"
#include "Driver.h"

#ifndef SERVER
#   include "../graphics/EndingGraphicsComponentTypes.h"
#endif

namespace td {

Projectile::Projectile(QObject* parent) : Unit(parent) {
    start_ = new QPointF(0,0);
    end_ = new QPointF(0,0);
    scale_ = 0.25;
    path_ = QLineF(end_->x(), end_->y(), start_->x(), start_->y());
    this->pos_ = QPointF(0,0);
}

Projectile::~Projectile() {
#ifndef SERVER
    switch (type_) {
    case PROJ_ARROW:
    case PROJ_ARROW_2:
    case PROJ_ARROW_3:
        new ArrowEndingGraphicsComponent(pos_);
        break;
    case PROJ_CANNON:
    case PROJ_CANNON_2:
    case PROJ_CANNON_3:
        new CannonEndingGraphicsComponent(pos_);
        break;
    case PROJ_FIRE:
    case PROJ_FIRE_2:
    case PROJ_FIRE_3:
        break;
    case PROJ_FLAK:
    case PROJ_FLAK_2:
    case PROJ_FLAK_3:
        break;
    case PROJ_TAR:
    case PROJ_TAR_2:
    case PROJ_TAR_3:
        break;
    }
#endif
    delete start_;
    delete end_;
}

void Projectile::initComponents() {
    if (type_ >= PROJ_ARROW && type_ <= PROJ_ARROW_6) {
        PLAY_SFX(this, SfxManager::projectileFireArrow);
        this->setHeight(10);
        this->setWidth(48);
        switch (type_) {
        case PROJ_ARROW:
            effectType_ = EFFECT_ARROW;
#ifndef SERVER
            setGraphicsComponent(new ArrowProjectileGraphicsComponent());
#endif
            break;
        case PROJ_ARROW_2:
            effectType_ = EFFECT_ARROW;
#ifndef SERVER
            setGraphicsComponent(new ArrowProjectileGraphicsComponent());
#endif
            break;
        case PROJ_ARROW_3:
            effectType_ = EFFECT_ARROW;
#ifndef SERVER
            setGraphicsComponent(new ArrowProjectileGraphicsComponent());
#endif
            break;
        case PROJ_ARROW_4:
            effectType_ = EFFECT_ARROW;
#ifndef SERVER
            setGraphicsComponent(new ArrowProjectileGraphicsComponent());
#endif
            break;
        case PROJ_ARROW_5:
            effectType_ = EFFECT_ARROW;
#ifndef SERVER
            setGraphicsComponent(new ArrowProjectileGraphicsComponent());
#endif
            break;
        case PROJ_ARROW_6:
            effectType_ = EFFECT_ARROW;
#ifndef SERVER
            setGraphicsComponent(new ArrowProjectileGraphicsComponent());
#endif
            break;
        }
        setInputComponent(new ArrowProjectileInputComponent());
        setPhysicsComponent(new ArrowProjectilePhysicsComponent());
    }
    if (type_ >= PROJ_CANNON && type_ <= PROJ_CANNON_6) {
        switch(type_) {
        case PROJ_CANNON:
            effectType_ = EFFECT_CANNON;
            this->setWidth(100);
            this->setHeight(100);
#ifndef SERVER
            setGraphicsComponent(new CannonProjectileGraphicsComponent());
#endif
            break;
        case PROJ_CANNON_2:
            effectType_ = EFFECT_CANNON;
            this->setWidth(100);
            this->setHeight(100);
#ifndef SERVER
            setGraphicsComponent(new CannonProjectileGraphicsComponent());
#endif
            break;
        case PROJ_CANNON_3:
            effectType_ = EFFECT_CANNON;
            this->setWidth(100);
            this->setHeight(100);
#ifndef SERVER
            setGraphicsComponent(new CannonProjectileGraphicsComponent());
#endif
            break;
        case PROJ_CANNON_4:
            effectType_ = EFFECT_CANNON;
            this->setWidth(100);
            this->setHeight(100);
#ifndef SERVER
            setGraphicsComponent(new CannonProjectileGraphicsComponent());
#endif
            break;
        case PROJ_CANNON_5:
            effectType_ = EFFECT_CANNON;
            this->setWidth(100);
            this->setHeight(100);
#ifndef SERVER
            setGraphicsComponent(new CannonProjectileGraphicsComponent());
#endif
            break;
        case PROJ_CANNON_6:
            effectType_ = EFFECT_CANNON;
            this->setWidth(100);
            this->setHeight(100);
#ifndef SERVER
            setGraphicsComponent(new CannonProjectileGraphicsComponent());
#endif
            break;
        }
        setInputComponent(new CannonProjectileInputComponent());
        setPhysicsComponent(new CannonProjectilePhysicsComponent());
        PLAY_SFX(this, SfxManager::projectileFireCannon);
    }
    if (type_ >= PROJ_FIRE && type_ <= PROJ_FIRE_6) {
        switch(type_) {
        case PROJ_FIRE:
            effectType_ = EFFECT_FIRE;
            this->setWidth(110);
            this->setHeight(36);
#ifndef SERVER
            setGraphicsComponent(new FireProjectileGraphicsComponent());
#endif
            break;
        case PROJ_FIRE_2:
            effectType_ = EFFECT_FIRE;
            this->setWidth(110);
            this->setHeight(36);
#ifndef SERVER
            setGraphicsComponent(new FireProjectileGraphicsComponent());
#endif
            break;
        case PROJ_FIRE_3:
            effectType_ = EFFECT_FIRE;
            this->setWidth(110);
            this->setHeight(36);
#ifndef SERVER
            setGraphicsComponent(new FireProjectileGraphicsComponent());
#endif
            break;
        case PROJ_FIRE_4:
            effectType_ = EFFECT_FIRE;
            this->setWidth(110);
            this->setHeight(36);
#ifndef SERVER
            setGraphicsComponent(new FireProjectileGraphicsComponent());
#endif
            break;
        case PROJ_FIRE_5:
            effectType_ = EFFECT_FIRE;
            this->setWidth(110);
            this->setHeight(36);
#ifndef SERVER
            setGraphicsComponent(new FireProjectileGraphicsComponent());
#endif
            break;
        case PROJ_FIRE_6:
            effectType_ = EFFECT_FIRE;
            this->setWidth(110);
            this->setHeight(36);
#ifndef SERVER
            setGraphicsComponent(new FireProjectileGraphicsComponent());
#endif
            break;
        }
        setInputComponent(new FireProjectileInputComponent());
        setPhysicsComponent(new FireProjectilePhysicsComponent());
        PLAY_SFX(this, SfxManager::projectileFireFlame);
    }
    if (type_ >= PROJ_TAR && type_ <= PROJ_TAR_6) {
        switch(type_) {
        case PROJ_TAR:
            effectType_ = EFFECT_TAR;
            this->setWidth(100);
            this->setHeight(100);
#ifndef SERVER
            setGraphicsComponent(new TarProjectileGraphicsComponent());
#endif
            break;
        case PROJ_TAR_2:
            effectType_ = EFFECT_TAR;
            this->setWidth(100);
            this->setHeight(100);
#ifndef SERVER
            setGraphicsComponent(new TarProjectileGraphicsComponent());
#endif
            break;
        case PROJ_TAR_3:
            effectType_ = EFFECT_TAR;
            this->setWidth(100);
            this->setHeight(100);
#ifndef SERVER
            setGraphicsComponent(new TarProjectileGraphicsComponent());
#endif
            break;
        case PROJ_TAR_4:
            effectType_ = EFFECT_TAR;
            this->setWidth(100);
            this->setHeight(100);
#ifndef SERVER
            setGraphicsComponent(new TarProjectileGraphicsComponent());
#endif
            break;
        case PROJ_TAR_5:
            effectType_ = EFFECT_TAR;
            this->setWidth(100);
            this->setHeight(100);
#ifndef SERVER
            setGraphicsComponent(new TarProjectileGraphicsComponent());
#endif
            break;
        case PROJ_TAR_6:
            effectType_ = EFFECT_TAR;
            this->setWidth(100);
            this->setHeight(100);
#ifndef SERVER
            setGraphicsComponent(new TarProjectileGraphicsComponent());
#endif
            break;
        }
        setInputComponent(new TarProjectileInputComponent());
        setPhysicsComponent(new TarProjectilePhysicsComponent());
        PLAY_SFX(this, SfxManager::projectileFireTar);
    }
    if (type_ >= PROJ_FLAK && type_ <= PROJ_FLAK_6) {
        switch(type_) {
        case PROJ_FLAK:
            effectType_ = EFFECT_FLAK;
            this->setWidth(40);
            this->setHeight(40);
#ifndef SERVER
            setGraphicsComponent(new FlakProjectileGraphicsComponent());
#endif
            break;
        case PROJ_FLAK_2:
            effectType_ = EFFECT_FLAK;
            this->setWidth(40);
            this->setHeight(40);
#ifndef SERVER
            setGraphicsComponent(new FlakProjectileGraphicsComponent());
#endif
            break;
        case PROJ_FLAK_3:
            effectType_ = EFFECT_FLAK;
            this->setWidth(40);
            this->setHeight(40);
#ifndef SERVER
            setGraphicsComponent(new FlakProjectileGraphicsComponent());
#endif
            break;
        case PROJ_FLAK_4:
            effectType_ = EFFECT_FLAK;
            this->setWidth(40);
            this->setHeight(40);
#ifndef SERVER
            setGraphicsComponent(new FlakProjectileGraphicsComponent());
#endif
            break;
        case PROJ_FLAK_5:
            effectType_ = EFFECT_FLAK;
            this->setWidth(40);
            this->setHeight(40);
#ifndef SERVER
            setGraphicsComponent(new FlakProjectileGraphicsComponent());
#endif
            break;
        case PROJ_FLAK_6:
            effectType_ = EFFECT_FLAK;
            this->setWidth(40);
            this->setHeight(40);
#ifndef SERVER
            setGraphicsComponent(new FlakProjectileGraphicsComponent());
#endif
            break;
            PLAY_SFX(this, SfxManager::projectileFireFlak);
            setInputComponent(new FlakProjectileInputComponent());
            setPhysicsComponent(new FlakProjectilePhysicsComponent());
        }
    }

    getInputComponent()->setParent(this);
    ((ProjectileInputComponent*)getInputComponent())->setPath(start_, end_);
    connect(enemy_, SIGNAL(signalNPCDied()), this, SLOT(enemyDied()));
}

void Projectile::setPath(QPointF source, QPointF target, Unit* enemy) {
    start_ = new QPointF(source);
    end_ = new QPointF(target);
    setEnemy(enemy);
}

void Projectile::networkRead(td::Stream* s) {
    Unit::networkRead(s);

    if (dirty_ & kDamage) {
        damage_ = s->readInt();
    }

    if (dirty_ & kStartPos) {
        start_->setX(s->readFloat());
        start_->setY(s->readFloat());
    }

    if (dirty_ & kEndPos) {
        end_->setX(s->readFloat());
        end_->setY(s->readFloat());
    }

    if (dirty_ & kTargetType) {
        enemy_ = (Unit*)getDriver()->findObject(s->readInt());
    }

    if (dirty_ & kType) {
        type_ = s->readInt();
    }
}

void Projectile::networkWrite(td::Stream* s) {
    Unit::networkWrite(s);

    if (dirty_ & kDamage) {
        s->writeInt(damage_);
    }

    if (dirty_ & kStartPos) {
        s->writeFloat(start_->x());
        s->writeFloat(start_->y());
    }

    if (dirty_ & kEndPos) {
        s->writeFloat(end_->x());
        s->writeFloat(end_->y());
    }

    if (dirty_ & kTargetType) {
        s->writeInt(enemy_->getID());
    }

    if (dirty_ & kType) {
        s->writeInt(type_);
    }
}

void Projectile::update() {
    input_->update();
    physics_->update(this);
#ifndef SERVER
    graphics_->update(this);
#endif
}

void Projectile::createBounds(){
    QVector<QPointF> points = QVector<QPointF>();
    QPointF *newPos = this->getEndPoint();
    QPointF point;
    QMatrix matrix = QMatrix();
    matrix.rotate(-this->getOrientation());

    point = QPointF(-((this->getWidth()/2) * this->getScale() ),
                        -((this->getHeight( )/2) * this->getScale())) * matrix;
    point += *newPos;
    points.append(point);
    point = QPointF((this->getWidth()/2) * this->getScale(),
                        -((this->getHeight()/2) * this->getScale())) * matrix;
    point += *newPos;
    points.append(point);
    point = QPointF((this->getWidth()/2) * this->getScale(),
                        (this->getHeight()/2) * this->getScale()) * matrix;
    point += *newPos;
    points.append(point);
    point = QPointF(-((this->getWidth()/2) * this->getScale()),
                        (this->getHeight()/2) * this->getScale()) * matrix;
    point += *newPos;
    points.append(point);
    point = QPointF(-((this->getWidth()/2) * this->getScale() ),
                        -((this->getHeight( )/2) * this->getScale())) * matrix;
    point += *newPos;
    points.append(point);

    this->setBounds(QPolygonF(points));
}

void Projectile::enemyDied() {
    enemy_ = NULL;
}

} /* end namespace td */
