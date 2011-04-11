#include "Effect.h"
#include "Driver.h"

namespace td {

Effect::Effect(Unit* unit, int duration, uint type, bool timerEnabled):
        GameObject(NULL), unit_(unit), duration_(duration),
        type_(type), timerEnabled_(timerEnabled), applyEnabled_(true),
        timer_(unit->getDriver()->getTimer()) {}

Effect::Effect(const Effect& e) : GameObject() {
    type_ = e.type_;
    unit_ = e.unit_;
    duration_ = e.duration_;
    velocityChangeValue_ = e.velocityChangeValue_;
    healthChangeValue_ = e.healthChangeValue_;
    timerEnabled_ = e.timerEnabled_;
    timer_ = e.timer_;
}

Effect& Effect::operator=(const Effect &rhs) {
    if (this != &rhs) {
        type_ = rhs.type_;
        unit_ = rhs.unit_;
        duration_ = rhs.duration_;
        velocityChangeValue_ = rhs.velocityChangeValue_;
        healthChangeValue_ = rhs.healthChangeValue_;
        timerEnabled_ = rhs.timerEnabled_;
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
    if (applyEnabled_) {
        this->apply();
    }
    if(timerEnabled_ == true) {
        countdown();
    }
}

void Effect::effectStop(uint type) {
    if (type_ == type) {
        applyEnabled_ = false; 
    }
}

void Effect::apply() {}

void Effect::countdown() {
    duration_--;
    if(duration_ <= 0){
        disconnect(timer_, SIGNAL(timeout()), this, SLOT(update()));
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
