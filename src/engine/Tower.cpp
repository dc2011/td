#include "Tower.h"
#include "CDriver.h"
namespace td {

void Tower::update() {
    graphics_->update(this);
    //physics_->update(this);
    CDriver::updateServer(this);
}
void Tower::initComponents() {
    GraphicsComponent* graphics = new TowerGraphicsComponent();
    this->setGraphicsComponent(graphics);
}
} // end of namespace td

