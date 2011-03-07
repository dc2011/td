#include "Effect.h"

namespace td {

    Effect::Effect(GameObject* unit, EffectType type):
        unit_(unit), type_(type){
    }

    Effect::~Effect(){
    }

    void Effect::apply(size_t duration, size_t speed){
        if(duration == 0){ //Apply effect to the unit once

        } else { //Apply effect to the unit for the duration

        }

    }

} /* end namespace td */
