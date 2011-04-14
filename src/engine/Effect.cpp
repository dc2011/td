#include "Effect.h"
#include "Driver.h"
#include "Player.h"
namespace td {

Effect::Effect(Unit* unit, uint type, int duration, bool timerEnabled):
        GameObject(NULL), unit_(unit), duration_(duration),
        type_(type), timerEnabled_(timerEnabled), applyEnabled_(true),
        timer_(unit->getDriver()->getTimer()) {

    if((unit_->getID() & 0xFF000000)>>24 != Player::clsIdx()) {
        connect(unit_, SIGNAL(stopEffect(uint)),
                         this, SLOT(effectStop(uint)));
    }
    connect(this, SIGNAL(effectFinished(Effect*)),
                     unit_, SLOT(deleteEffect(Effect*)));
    connect(timer_, SIGNAL(timeout()),
                     this, SLOT(update()));
}

Effect::Effect(const Effect& e) : GameObject() {
    type_ = e.type_;
    unit_ = e.unit_;
    duration_ = e.duration_;
    velocityChangeValue_ = e.velocityChangeValue_;
    healthChangeValue_ = e.healthChangeValue_;
    timerEnabled_ = e.timerEnabled_;
    timer_ = e.timer_;
    if((unit_->getID() & 0xFF000000)>>24 != Player::clsIdx()) {
        connect(unit_, SIGNAL(stopEffect(uint)),
                         this, SLOT(effectStop(uint)));
    }
    connect(this, SIGNAL(effectFinished(Effect*)),
                     unit_, SLOT(deleteEffect(Effect*)));
    connect(timer_, SIGNAL(timeout()),
                     this, SLOT(update()));
}

Effect& Effect::operator=(const Effect &rhs) {
    if (this != &rhs) {
        type_ = rhs.type_;
        unit_ = rhs.unit_;
        duration_ = rhs.duration_;
        velocityChangeValue_ = rhs.velocityChangeValue_;
        healthChangeValue_ = rhs.healthChangeValue_;
        timerEnabled_ = rhs.timerEnabled_;
        if((unit_->getID() & 0xFF000000)>>24 != Player::clsIdx()) {
            connect(unit_, SIGNAL(stopEffect(uint)),
                             this, SLOT(effectStop(uint)));
        }
        connect(this, SIGNAL(effectFinished(Effect*)),
                         unit_, SLOT(deleteEffect(Effect*)));
        connect(timer_, SIGNAL(timeout()),
                         this, SLOT(update()));
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
    if((unit_->getID() & 0xFF000000)>>24 != Player::clsIdx()) {
        disconnect(unit_, SIGNAL(stopEffect(uint)),
                         this, SLOT(effectStop(uint)));
    }
    disconnect(this, SIGNAL(effectFinished(Effect*)),
                     unit_, SLOT(deleteEffect(Effect*)));
    disconnect(timer_, SIGNAL(timeout()),
                     this, SLOT(update()));
}

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
