#include "Collectable.h"
#include "../engine/CDriver.h"
#include "../input/CollectableInputComponent.h"
#include "../physics/CollectablePhysicsComponent.h"
#include "../graphics/CollectableGraphicsComponentTypes.h" 
namespace td {

Collectable::Collectable(QObject* parent) 
        : Unit(parent) {
    start_ = new QPointF(0,0);
    end_ = new QPointF(0,0);
    scale_ = 1;
    path_ = QLineF(end_->x(), end_->y(), start_->x(), start_->y());
    this->pos_ = QPointF(0,0);
    this->setHeight(24);
    this->setWidth(24);
}

Collectable::~Collectable() {
    delete start_;
    delete end_;
}

void Collectable::networkRead(Stream* s) {
    Unit::networkRead(s);

    if (dirty_ & kType) {
        type_ = s->readInt();
    }
    if (dirty_ & kStartPos) {
        start_->setX(s->readFloat());
        start_->setY(s->readFloat());
    }
    if (dirty_ & kEndPos) {
        end_->setX(s->readFloat());
        end_->setY(s->readFloat());
    }
}

void Collectable::networkWrite(Stream* s) {
    Unit::networkWrite(s);

    if (dirty_ & kType) {
        s->writeInt(type_);
    }
    if (dirty_ & kStartPos) {
        s->writeFloat(start_->x());
        s->writeFloat(start_->y());
    }
    if (dirty_ & kEndPos) {
        s->writeFloat(end_->x());
        s->writeFloat(end_->y());
    }
}

void Collectable::initComponents() {

    switch (type_) {
        case RESOURCE_WOOD:
            input_ = new CollectableInputComponent();
            physics_ = new CollectablePhysicsComponent();
#ifndef SERVER
            setGraphicsComponent(new WoodCollectableGraphicsComponent());
#endif
            break;

        case RESOURCE_STONE:
            input_ = new CollectableInputComponent();
            physics_ = new CollectablePhysicsComponent();
#ifndef SERVER
            setGraphicsComponent(new StoneCollectableGraphicsComponent());
#endif
            break;

        case RESOURCE_BONE:
            input_ = new CollectableInputComponent();
            physics_ = new CollectablePhysicsComponent();
#ifndef SERVER
            setGraphicsComponent(new BoneCollectableGraphicsComponent());
#endif
            break;

        case RESOURCE_TAR:
            input_ = new CollectableInputComponent();
            physics_ = new CollectablePhysicsComponent();
#ifndef SERVER
            setGraphicsComponent(new TarCollectableGraphicsComponent());
#endif
            break;

        case RESOURCE_GEM:
            input_ = new CollectableInputComponent();
            physics_ = new CollectablePhysicsComponent();
#ifndef SERVER
            setGraphicsComponent(new GemCollectableGraphicsComponent());
#endif
            break;
            
    }
    input_->setParent(this);
    ((CollectableInputComponent*)input_)->setPath(start_, end_);
}

void Collectable::setPath(QPointF source, QVector2D velocity) {
    start_ = new QPointF(source);
    end_ = new QPointF(source + velocity.toPointF());
}

void Collectable::update() {

    if (input_ != NULL) {
        input_->update();
    }
    if (physics_ != NULL) {
        physics_->update(this);
    }
    if (graphics_ != NULL) {
        graphics_->update(this);
    }
}

} // end namespace td

