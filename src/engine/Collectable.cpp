#include "Collectable.h"
#include "../engine/CDriver.h"
#include "../physics/CollectablePhysicsComponent.h"

namespace td {

Collectable::Collectable(QObject* parent) 
        : Unit(parent) {
    start_ = new QPointF(0,0);
    end_ = new QPointF(0,0);
    scale_ = 0.25;
    path_ = QLineF(end_->x(), end_->y(), start_->x(), start_->y());
    this->pos_ = QPointF(0,0);
    this->setHeight(10);
    this->setWidth(48);
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
   // ResourceItemInputComponent* input;

    switch (type_) {
        case COLLECT_RESOURCE:
            //input = new ResourceItemPhysicsComponent();
            //input->setParent(this);
            setPhysicsComponent(new CollectablePhysicsComponent(70));
#ifndef SERVER
            //setGraphicsComponent(new ResourceItemGraphicsComponent());
#endif
            break;
/*
        case COLLECT_GEM;
            input = new GemPhysicsComponent();
            input->setParent(this);
            setPhysicsComponent(new GemPhysicsComponent());
#ifndef SERVER
            setGraphicsComponent(new GemGraphicsComponent());
#endif
            break;
            */
    }

#ifndef SERVER
    if (!((CDriver*) getDriver())->isSinglePlayer()) {
        delete getInputComponent();
        delete getPhysicsComponent();
        setInputCopmonent(NULL);
        setPhysicsCoponent(NULL);
    }
#endif
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

