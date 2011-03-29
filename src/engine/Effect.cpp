#include "Effect.h"
#include "CDriver.h"

namespace td {

Effect::Effect(Unit* unit, EffectType type):
        GameObject(NULL), unit_(unit), type_(type), duration_(20), healthChangeValue_(-1), velocityChangeValue_(0,0){}

Effect::~Effect(){}

void Effect::update(){
    this->apply();
}

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

    duration_--;
    if(duration_ == 0){
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
