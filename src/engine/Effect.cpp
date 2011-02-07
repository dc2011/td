#include "Effect.h"

using namespace std;

Effect::Effect(Unit* unit) {
    unit_ = unit;
}

void Effect::Apply(){
    //Apply effect to the unit
}

size_t Effect::GetDuration(){
    return duration_;
}

void Effect::SetDuration(size_t duration){
    duration_ = duration;
}
