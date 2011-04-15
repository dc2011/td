#include "TowerGraphicsComponent.h"
#include "../engine/Tower.h"
#include "../physics/TowerPhysicsComponent.h"
#include <QPointF>
#include <QPainter>
#include "../engine/CDriver.h"
#include <QGradientStops>

namespace td {

TowerGraphicsComponent::~TowerGraphicsComponent() {
    disconnect();
    delete rangeCircle_;
}

struct DrawParamsTower {
    /** location */
    QPointF pos;
    /** in degrees 0 is up 180 down... */
    int degrees;
    /** normal is 1 .5 is half 2 is double */
    float scale;

};

void TowerGraphicsComponent::update(GameObject* obj) {
    Tower* tower = (Tower*)obj;
    tower->resetDirty();

    radius_ = ((TowerPhysicsComponent*)(tower->getPhysicsComponent()))->getRadius();

    DrawParams* dp = new DrawParams();
    dp->pos     = tower->getPos();
    //dp->moving  = 1;
    //player->getVelocity().length() != 0;
    dp->scale   = 1;//tower->getScale();
    dp->degrees = tower->getOrientation();
    emit signalDraw(dp, this, LAYER_TOWER);
}


void TowerGraphicsComponent::initRangeCircle(QColor color) {
    visibleRange_ = false;
    rangeCircle_ = new QGraphicsEllipseItem(OFFSCREEN, OFFSCREEN, 1,1);
    QPen pen(color);
    pen.setWidth(3);
    rangeCircle_->setBrush(QBrush(Qt::transparent));
    rangeCircle_->setPen(pen);
    CDriver::instance()->getMainWindow()->getScene()->addItem(rangeCircle_);
}
void TowerGraphicsComponent::draw(void* dp, int layer) {
    DrawParams * dps = (DrawParams*) dp;
    if (visibleRange_) {

        QPointF point = dps->pos;
        rangeCircle_->setRect(point.x()-radius_, point.y()-radius_, radius_ * 2, radius_ * 2);
        rangeCircle_->setOpacity(.5);

        rangeCircle_->setVisible(true);
        rangeCircle_->update();
    } else {
        rangeCircle_->setVisible(false);
        rangeCircle_->update();
    }
    GraphicsComponent::draw(dp, layer);

}
} /* end namespace td */
