#include "Effect.h"

namespace td {

    Effect::Effect(Unit* unit, EffectType type):
        unit_(unit), type_(type), duration_(1){
    }

    Effect::~Effect(){
    }

    void Effect::update(){ }

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
            break;
        }
    }

} /* end namespace td */
