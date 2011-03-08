#include "Tower.h"
#include "CDriver.h"
namespace td {

void Tower::update() {
    graphics_->update(this);
    //physics_->update(this);
    CDriver::updateServer(this);
}

} // end of namespace td

