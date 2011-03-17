#include "Effect.h"
#include "CDriver.h"

namespace td {

Effect::Effect(Unit* unit, EffectType type):
        GameObject(NULL), unit_(unit), type_(type), duration_(40){}

Effect::~Effect(){}

void Effect::update(){
    this->apply();
}

void Effect::apply(){
    QVector2D tmpVelocity(0,0);
    switch (type_){
    case healthChange:
        break;
    case damageChange:
        break;
    case speedChange:
        break;
    case velocityChange:
        break;
    case stunned:
        unit_->setVelocity(tmpVelocity);
        break;
    default:
        return;
    }

    duration_--;
    if(duration_ == 0){
#ifndef SERVER
        QObject::disconnect(CDriver::getTimer(), SIGNAL(timeout()),
                this, SLOT(update()));
#endif
        emit effectFinished(this);
    }
}

} /* end namespace td */
