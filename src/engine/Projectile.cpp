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

namespace td {

Projectile::Projectile(QObject* parent) : Unit(parent) {
    start_ = new QPointF(0,0);
    end_ = new QPointF(0,0);
    scale_ = 0.25;
    path_ = QLineF(end_->x(), end_->y(), start_->x(), start_->y());
    this->pos_ = QPointF(0,0);
}

Projectile::~Projectile() {
    delete start_;
    delete end_;
}

void Projectile::initComponents() {
    if (type_ >= PROJ_ARROW && type_ <= PROJ_ARROW_5) {
        PLAY_SFX(this, SfxManager::projectileFireArrow);
        switch (type_) {
        case PROJ_ARROW:
            effectType_ = EFFECT_ARROW;
#ifndef SERVER
            setGraphicsComponent(new ArrowProjectileGraphicsComponent());
#endif
            break;
        case PROJ_ARROW_2:
            effectType_ = EFFECT_ARROW_2;
#ifndef SERVER
            setGraphicsComponent(new ArrowProjectileGraphicsComponent());
#endif
            break;
        case PROJ_ARROW_3:
            effectType_ = EFFECT_ARROW_3;
#ifndef SERVER
            setGraphicsComponent(new ArrowProjectileL2GraphicsComponent());
#endif
            break;
        case PROJ_ARROW_4:
            effectType_ = EFFECT_ARROW_4;
#ifndef SERVER
            setGraphicsComponent(new ArrowProjectileL2GraphicsComponent());
#endif
            break;
        case PROJ_ARROW_5:
            effectType_ = EFFECT_ARROW_5;
#ifndef SERVER
            setGraphicsComponent(new ArrowProjectileL3GraphicsComponent());
#endif
            break;
        }
        setInputComponent(new ArrowProjectileInputComponent());
        setPhysicsComponent(new ArrowProjectilePhysicsComponent());
    }
    if (type_ >= PROJ_CANNON && type_ <= PROJ_CANNON_5) {
        switch(type_) {
        case PROJ_CANNON:
            effectType_ = EFFECT_CANNON;
            this->setWidth(CANNON_WIDTH);
            this->setHeight(CANNON_HEIGHT);
#ifndef SERVER
            setGraphicsComponent(new CannonProjectileGraphicsComponent());
#endif
            break;
        case PROJ_CANNON_2:
            effectType_ = EFFECT_CANNON_2;
            this->setWidth(CANNON_WIDTH_2);
            this->setHeight(CANNON_HEIGHT_2);
#ifndef SERVER
            setGraphicsComponent(new CannonProjectileGraphicsComponent());
#endif
            break;
        case PROJ_CANNON_3:
            effectType_ = EFFECT_CANNON_3;
            this->setWidth(CANNON_WIDTH_3);
            this->setHeight(CANNON_HEIGHT_3);
#ifndef SERVER
            setGraphicsComponent(new CannonProjectileL2GraphicsComponent());
#endif
            break;
        case PROJ_CANNON_4:
            effectType_ = EFFECT_CANNON_4;
            this->setWidth(CANNON_WIDTH_4);
            this->setHeight(CANNON_HEIGHT_4);
#ifndef SERVER
            setGraphicsComponent(new CannonProjectileL2GraphicsComponent());
#endif
            break;
        case PROJ_CANNON_5:
            effectType_ = EFFECT_CANNON_5;
            this->setWidth(CANNON_WIDTH_5);
            this->setHeight(CANNON_HEIGHT_5);
#ifndef SERVER
            setGraphicsComponent(new CannonProjectileL3GraphicsComponent());
#endif
            break;
        }
        setInputComponent(new CannonProjectileInputComponent());
        setPhysicsComponent(new CannonProjectilePhysicsComponent());
        PLAY_SFX(this, SfxManager::projectileFireCannon);
    }
    if (type_ >= PROJ_FIRE && type_ <= PROJ_FIRE_5) {
        switch(type_) {
        case PROJ_FIRE:
            effectType_ = EFFECT_FIRE;
            this->setWidth(FLAME_WIDTH);
            this->setHeight(FLAME_HEIGHT);
            this->setScale(1.0);
#ifndef SERVER
            setGraphicsComponent(new FireProjectileL1GraphicsComponent());
#endif
            break;
        case PROJ_FIRE_2:
            effectType_ = EFFECT_FIRE_2;
            this->setWidth(RADIUS_FLAME_2);
            this->setHeight(FLAME_HEIGHT * RADIUS_FLAME_2 / 90);
            this->setScale(RADIUS_FLAME_2 / 90);
#ifndef SERVER
            setGraphicsComponent(new FireProjectileL1GraphicsComponent());
#endif
            break;
        case PROJ_FIRE_3:
            effectType_ = EFFECT_FIRE_3;
            this->setWidth(RADIUS_FLAME_3);
            this->setHeight(FLAME_HEIGHT * RADIUS_FLAME_3 / 90);
            this->setScale(RADIUS_FLAME_3 / 90);
#ifndef SERVER
            setGraphicsComponent(new FireProjectileL2GraphicsComponent());
#endif
            break;
        case PROJ_FIRE_4:
            effectType_ = EFFECT_FIRE_4;
            this->setWidth(RADIUS_FLAME_4);
            this->setHeight(FLAME_HEIGHT * RADIUS_FLAME_4 / 90);
            this->setScale(RADIUS_FLAME_4 / 90);
#ifndef SERVER
            setGraphicsComponent(new FireProjectileL2GraphicsComponent());
#endif
            break;
        case PROJ_FIRE_5:
            effectType_ = EFFECT_FIRE_5;
            this->setWidth(RADIUS_FLAME_5);
            this->setHeight(FLAME_HEIGHT * RADIUS_FLAME_5 / 80);
            this->setScale(RADIUS_FLAME_5 / 80);
#ifndef SERVER
            setGraphicsComponent(new FireProjectileL3GraphicsComponent());
#endif
            break;
        }
        setInputComponent(new FireProjectileInputComponent());
        setPhysicsComponent(new FireProjectilePhysicsComponent());
        PLAY_SFX(this, SfxManager::projectileFireFlame);
    }
    if (type_ >= PROJ_TAR && type_ <= PROJ_TAR_5) {
        switch(type_) {
        case PROJ_TAR:
            effectType_ = EFFECT_TAR;
            this->setWidth(TAR_WIDTH);
            this->setHeight(TAR_HEIGHT);
#ifndef SERVER
            setGraphicsComponent(new TarProjectileGraphicsComponent());
#endif
            break;
        case PROJ_TAR_2:
            effectType_ = EFFECT_TAR_2;
            this->setWidth(TAR_WIDTH_2);
            this->setHeight(TAR_HEIGHT_2);
#ifndef SERVER
            setGraphicsComponent(new TarProjectileGraphicsComponent());
#endif
            break;
        case PROJ_TAR_3:
            effectType_ = EFFECT_TAR_3;
            this->setWidth(TAR_WIDTH_3);
            this->setHeight(TAR_HEIGHT_3);
#ifndef SERVER
            setGraphicsComponent(new TarProjectileL2GraphicsComponent());
#endif
            break;
        case PROJ_TAR_4:
            effectType_ = EFFECT_TAR_4;
            this->setWidth(TAR_WIDTH_4);
            this->setHeight(TAR_HEIGHT_4);
#ifndef SERVER
            setGraphicsComponent(new TarProjectileL2GraphicsComponent());
#endif
            break;
        case PROJ_TAR_5:
            effectType_ = EFFECT_TAR_5;
            this->setWidth(TAR_WIDTH_5);
            this->setHeight(TAR_HEIGHT_5);
#ifndef SERVER
            setGraphicsComponent(new TarProjectileL3GraphicsComponent());
#endif
            break;
        }
        setInputComponent(new TarProjectileInputComponent());
        setPhysicsComponent(new TarProjectilePhysicsComponent());
        PLAY_SFX(this, SfxManager::projectileFireTar);
    }
    if (type_ >= PROJ_FLAK && type_ <= PROJ_FLAK_5) {
        switch(type_) {
        case PROJ_FLAK:
            effectType_ = EFFECT_FLAK;
            this->setWidth(FLAK_WIDTH);
            this->setHeight(FLAK_HEIGHT);
#ifndef SERVER
            setGraphicsComponent(new FlakProjectileGraphicsComponent());
#endif
            break;
        case PROJ_FLAK_2:
            effectType_ = EFFECT_FLAK_2;
            this->setWidth(FLAK_WIDTH_2);
            this->setHeight(FLAK_HEIGHT_2);
#ifndef SERVER
            setGraphicsComponent(new FlakProjectileGraphicsComponent());
#endif
            break;
        case PROJ_FLAK_3:
            effectType_ = EFFECT_FLAK_3;
            this->setWidth(FLAK_WIDTH_3);
            this->setHeight(FLAK_HEIGHT_3);
#ifndef SERVER
            setGraphicsComponent(new FlakProjectileL2GraphicsComponent());
#endif
            break;
        case PROJ_FLAK_4:
            effectType_ = EFFECT_FLAK_4;
            this->setWidth(FLAK_WIDTH_4);
            this->setHeight(FLAK_HEIGHT_4);
#ifndef SERVER
            setGraphicsComponent(new FlakProjectileL2GraphicsComponent());
#endif
            break;
        case PROJ_FLAK_5:
            effectType_ = EFFECT_FLAK_5;
            this->setWidth(FLAK_WIDTH_5);
            this->setHeight(FLAK_HEIGHT_5);
#ifndef SERVER
            setGraphicsComponent(new FlakProjectileL3GraphicsComponent());
#endif
            break;
        }
        PLAY_SFX(this, SfxManager::projectileFireFlak);
        setInputComponent(new FlakProjectileInputComponent());
        setPhysicsComponent(new FlakProjectilePhysicsComponent());
    }

    getInputComponent()->setParent(this);
    ((ProjectileInputComponent*)getInputComponent())->setPath(start_, end_);
    if(enemy_ != NULL) {
        connect(enemy_, SIGNAL(signalNPCDied()), this, SLOT(enemyDied()));
    }
}

void Projectile::setPath(QPointF source, QPointF target, Unit* enemy) {
    if (type_ >= PROJ_FIRE && type_ <= PROJ_FIRE_5) {
        QLineF distance = QLineF(source.x(), source.y(),
                target.x(), target.y());
        switch(type_) {
        case PROJ_FIRE_2:
            distance.setLength(distance.length() * 90 / RADIUS_FLAME_2);
            break;
        case PROJ_FIRE_3:
            distance.setLength(distance.length() * 90 / RADIUS_FLAME_3);
            break;
        case PROJ_FIRE_4:
            distance.setLength(distance.length() * 90 / RADIUS_FLAME_4);
            break;
        case PROJ_FIRE_5:
            distance.setLength(distance.length() * 120 / RADIUS_FLAME_5);
            break;
        }
        end_ = new QPointF(distance.p2());
    } else {
        end_ = new QPointF(target);
    }
    start_ = new QPointF(source);
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
