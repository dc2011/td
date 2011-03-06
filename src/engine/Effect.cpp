#include "Effect.h"

namespace td {

Effect::Effect(Unit* unit) {
    unit_ = unit;
}

void Effect::apply(){
    //Apply effect to the unit
}

size_t Effect::getDuration(){
    return duration_;
}

void Effect::setDuration(size_t duration){
    duration_ = duration;
}

} /* end namespace td */
