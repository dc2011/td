#include "Effect.h"
#include "Driver.h"
#include "Player.h"
namespace td {

Effect::Effect(Unit* unit, uint type, int duration, bool timerEnabled):
        GameObject(NULL), unit_(unit), type_(type),
        duration_(duration), timerEnabled_(timerEnabled) {
}

Effect::Effect(const Effect& e) : GameObject() {
    type_ = e.type_;
    unit_ = e.unit_;
    duration_ = e.duration_;
    velocityChangeValue_ = e.velocityChangeValue_;
    healthChangeValue_ = e.healthChangeValue_;
    timerEnabled_ = e.timerEnabled_;
    connect(this, SIGNAL(effectFinished(Effect*)),
                     unit_, SLOT(deleteEffect(Effect*)));
}

Effect& Effect::operator=(const Effect &rhs) {
    if (this != &rhs) {
        type_ = rhs.type_;
        unit_ = rhs.unit_;
        duration_ = rhs.duration_;
        velocityChangeValue_ = rhs.velocityChangeValue_;
        healthChangeValue_ = rhs.healthChangeValue_;
        timerEnabled_ = rhs.timerEnabled_;
        connect(this, SIGNAL(effectFinished(Effect*)),
                         unit_, SLOT(deleteEffect(Effect*)));
    }
    return *this;
}

bool Effect::operator==(const Effect &e) const {
    return (type_ == e.type_);
}

bool Effect::operator!=(const Effect &e) const {
    return (type_ != e.type_);
}

Effect::~Effect(){
    disconnect(this, SIGNAL(effectFinished(Effect*)),
                     unit_, SLOT(deleteEffect(Effect*)));
}

void Effect::update(){
    apply();
    if(timerEnabled_ == true) {
        countdown();
    }
}

void Effect::apply() {}

void Effect::countdown() {
    duration_--;
    if(duration_ <= 0){
        emit effectFinished(this);
    }
}

void Effect::setDuration(size_t duration) {
    duration_ = duration;
}

size_t Effect::getDuration() {
    return duration_;
}

void Effect::setVelocityChangeValue(float velocity) {
    velocityChangeValue_ = velocity;
}

float Effect::getVelocityChangeValue() {
    return velocityChangeValue_;
}

void Effect::setHealthChangeValue(int healthChange) {
    healthChangeValue_ = healthChange;
}

int Effect::getHealthChangeValue() {
    return healthChangeValue_;
}

} /* end namespace td */
