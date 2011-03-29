#include "Effect.h"
#include "CDriver.h"

namespace td {

Effect::Effect(Unit* unit, int duration):
        GameObject(NULL), unit_(unit), duration_(duration) {}

Effect::~Effect(){}

void Effect::update(){
    this->apply();
    countdown();
}
/*
void Effect::apply(){
    switch (type_){
    case healthChange:
        qDebug("Before health: ");
        unit_->setHealth(unit_->getHealth() + healthChangeValue_);
        break;
    case damageChange:
        break;
    case speedChange:
        break;
    case velocityChange:
        break;
    case stunned:
        unit_->setVelocity(velocityChangeValue_);
        break;
    default:
        return;
    }
    */
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
