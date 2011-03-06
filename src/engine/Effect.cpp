#include "Effect.h"

Effect::Effect(Unit* unit, size_t duration):
    unit_(unit), duration_(duration){
}

Effect::~Effect(){
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
