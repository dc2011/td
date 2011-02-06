#include "Unit.h"

Unit::~Unit() {
    delete input_;
    delete physics_;
}
