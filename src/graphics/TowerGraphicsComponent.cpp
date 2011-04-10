#include "TowerGraphicsComponent.h"
#include "../engine/Tower.h"
#include "../physics/TowerPhysicsComponent.h"
#include <QPointF>
#include <QPainter>

namespace td {

TowerGraphicsComponent::~TowerGraphicsComponent() {}

void TowerGraphicsComponent::update(GameObject* obj) {
    Tower* tower = (Tower*)obj;
    //if (!tower->getDirtyStatus()) {//checks if object is dirty.
    //    return;
    //}
    tower->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = tower->getPos();
    dp->moving  = 1;
    //player->getVelocity().length() != 0;
    dp->scale   = 1;//tower->getScale();
    dp->degrees = tower->getOrientation();
    emit signalDraw(dp, this, LAYER_TOWER);
}


void TowerGraphicsComponent::initRangeCircle(GameObject* obj) {
    visibleRange_ = false;
    Tower* tower = (Tower*)obj;
    QPointF point = tower->getPos();


    int radius = (TowerPhysicsComponent*)(tower->getPhysicsComponent())->getRadius();
    rangeCircle_ = new QGraphicsEllipseItem(point.x()-radius, point.y()-radius,
                                            radius * 2, radius * 2);
    rangeCircle_->setBrush(QBrush(QT::white));
    rangeCircle_->setOpacity(.5);
    CDriver::instance()->getMainWindow()->getScene()->addItem(rangeCircle_);
}
void TowerGraphicsComponent::draw(DrawParams* dp, int layer) {
    if (visibleRange_) {
        rangeCircle_->setVisible(true);
        rangeCircle_->update();
    } else {
        rangeCircle_->setVisible(false);
        rangeCircle_->update();
    }
    GraphicsComponent::draw(dp, layer);

}
} /* end namespace td */
