#include "TowerGraphicsComponent.h"
#include "../engine/Tower.h"
#include "../physics/TowerPhysicsComponent.h"
#include <QPointF>
#include <QPainter>
#include "../engine/CDriver.h"

namespace td {

TowerGraphicsComponent::~TowerGraphicsComponent() {}

void TowerGraphicsComponent::update(GameObject* obj) {
    Tower* tower = (Tower*)obj;
    //if (!tower->getDirtyStatus()) {//checks if object is dirty.
    //    return;
    //}
    tower->resetDirty();
    radius_ = ((TowerPhysicsComponent*)(tower->getPhysicsComponent()))->getRadius();

    DrawParams* dp = new DrawParams();
    dp->pos     = tower->getPos();
    dp->moving  = 1;
    //player->getVelocity().length() != 0;
    dp->scale   = 1;//tower->getScale();
    dp->degrees = tower->getOrientation();
    emit signalDraw(dp, this, LAYER_TOWER);
}


void TowerGraphicsComponent::initRangeCircle(QColor color) {
    visibleRange_ = false;

    rangeCircle_ = new QGraphicsEllipseItem(OFFSCREEN, OFFSCREEN, 1,1);

    rangeCircle_->setBrush(QBrush(color));
    CDriver::instance()->getMainWindow()->getScene()->addItem(rangeCircle_);
}
void TowerGraphicsComponent::draw(DrawParams* dp, int layer) {
    if (visibleRange_) {

        QPointF point = dp->pos;
        rangeCircle_->setRect(point.x()-radius_, point.y()-radius_, radius_ * 2, radius_ * 2);
        rangeCircle_->setOpacity(.1);

        rangeCircle_->setVisible(true);
        rangeCircle_->update();
    } else {
        rangeCircle_->setVisible(false);
        rangeCircle_->update();
    }
    GraphicsComponent::draw(dp, layer);

}
} /* end namespace td */
