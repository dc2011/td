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

//#include <QDebug>
//virtual void draw(void *dp, int layer) {
//      if
//  static int count = 0;
//    qDebug() << "Drawing Resource" << ++count;
//GraphicsComponent::draw(dp,layer);
//this->disconnect();
//}



void TowerGraphicsComponent::update(GameObject* obj) {
    Tower* tower = (Tower*)obj;
    tower->resetDirty();

    DrawParamsTower* dp = new DrawParamsTower();

    radius_ = ((TowerPhysicsComponent*)(tower->getPhysicsComponent()))->getRadius();
    dp->pos     = tower->getPos();
    //dp->moving  = 1;
    //player->getVelocity().length() != 0;
    dp->scale   = 1;//tower->getScale();
    dp->degrees = tower->getOrientation();
    dp->displayRadius = visibleRange_;
    if (this->oldDegrees_ != dp->degrees || this->oldPos_ != dp->pos
        || this->oldVisibleRange_ != dp->displayRadius) {
        oldDegrees_ = dp->degrees;
        oldPos_ = dp->pos;
        oldVisibleRange_ = dp->displayRadius;
        emit signalDraw(dp, this, LAYER_TOWER);
    } else {
        delete dp;
    }
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
    DrawParamsTower * dps = (DrawParamsTower*) dp;
    if (dps->displayRadius) {
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
