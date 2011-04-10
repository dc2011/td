#include "Effect.h"
#include "CDriver.h"

namespace td {

Effect::Effect(Unit* unit, int duration, bool timerEnabled, uint type):
        GameObject(NULL), unit_(unit), duration_(duration),
        timerEnabled_(timerEnabled), type_(type) {}

Effect::Effect(const Effect& e) : GameObject() {
    type_ = e.type_;
    unit_ = e.unit_;
    duration_ = e.duration_;
    velocityChangeValue_ = e.velocityChangeValue_;
    healthChangeValue_ = e.healthChangeValue_;
}

Effect& Effect::operator=(const Effect &rhs) {
    if (this != &rhs) {
        type_ = rhs.type_;
        unit_ = rhs.unit_;
        duration_ = rhs.duration_;
        velocityChangeValue_ = rhs.velocityChangeValue_;
        healthChangeValue_ = rhs.healthChangeValue_;
    }

    return *this;
}

bool Effect::operator==(const Effect &e) const {
    return (type_ == e.type_);
}

bool Effect::operator!=(const Effect &e) const {
    return (type_ != e.type_);
}

Effect::~Effect(){}

void Effect::update(){
    this->apply();
    if(timerEnabled_ == true) {
    countdown();
    }
}

void Effect::apply() {}

void Effect::countdown() {
    duration_--;
    if(duration_ <= 0){
        disconnect(unit_->getDriver()->getTimer(), SIGNAL(timeout()),
              this, SLOT(update()));
        emit effectFinished(this);
    }
}

void Effect::setDuration(size_t duration) {
    duration_ = duration;
}

size_t Effect::getDuration() {
    return duration_;
}

void Effect::setVelocityChangeValue(QVector2D velocity) {
    velocityChangeValue_ = velocity;
}

QVector2D Effect::getVelocityChangeValue() {
    return velocityChangeValue_;
}

void Effect::setHealthChangeValue(int healthChange) {
    healthChangeValue_ = healthChange;
}

int Effect::getHealthChangeValue() {
    return healthChangeValue_;
}

} /* end namespace td */
