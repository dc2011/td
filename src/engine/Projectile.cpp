#include "Projectile.h"
#include "NPC.h"
#ifndef SERVER
#include "CDriver.h"
#endif
#include "EffectTypes.h"
#include "../util/defines.h"
#include "../input/ProjectileInputComponent.h"
#include "../input/ProjectileInputComponentTypes.h"
#include "../physics/ProjectilePhysicsComponentTypes.h"
#include "../graphics/ProjectileGraphicsComponentTypes.h"
#include "Driver.h"
#include "../graphics/EndingGraphicsComponentTypes.h"

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
        new ArrowEndingGraphicsComponent(pos_);
        break;
    case PROJ_CANNON:
        new CannonEndingGraphicsComponent(pos_);
        break;
    case PROJ_FIRE:
        break;
    case PROJ_FLAK:
        break;
    case PROJ_TAR:
        break;
    }
#endif
    delete start_;
    delete end_;
}

void Projectile::initComponents() {
    switch(type_) {
        case PROJ_ARROW:
            this->setHeight(10);
            this->setWidth(48);
            setInputComponent(new ArrowProjectileInputComponent());
            setPhysicsComponent(new ArrowProjectilePhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new ArrowProjectileGraphicsComponent());
#endif
            break;

        case PROJ_CANNON:
            this->setWidth(100);
            this->setHeight(100);
            setInputComponent(new CannonProjectileInputComponent());
            setPhysicsComponent(new CannonProjectilePhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new CannonProjectileGraphicsComponent());
#endif
            break;

        case PROJ_FIRE:
            this->setWidth(110);
            this->setHeight(36);
            setInputComponent(new FireProjectileInputComponent());
            setPhysicsComponent(new FireProjectilePhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new FireProjectileGraphicsComponent());
#endif
            break;

        case PROJ_TAR:
            this->setWidth(100);
            this->setHeight(100);
            setInputComponent(new TarProjectileInputComponent());
            setPhysicsComponent(new TarProjectilePhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new TarProjectileGraphicsComponent());
#endif
            break;

        case PROJ_FLAK:
            this->setWidth(40);
            this->setHeight(40);
            setInputComponent(new FlakProjectileInputComponent());
            setPhysicsComponent(new FlakProjectilePhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new FlakProjectileGraphicsComponent());
#endif
            break;
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
