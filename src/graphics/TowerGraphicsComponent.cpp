#include "TowerGraphicsComponent.h"
#include <QPointF>
#include <QPainter>
#include <QGradientStops>
#include "../engine/CDriver.h"
#include "../engine/Tower.h"
#include "../physics/TowerPhysicsComponent.h"

namespace td {
    
TowerGraphicsComponent::TowerGraphicsComponent()
        : GraphicsComponent(), constructed_(false), oldRotation_(-1),
        oldFiring_(false), oldRadius_(false), firing_(false),
        timerRunning_(false), timerID_(0), reloadTime_(0),
        hasFiringAnimation_(false) {
}

TowerGraphicsComponent::~TowerGraphicsComponent() {
    disconnect();
    delete rangeCircle_;
}

void TowerGraphicsComponent::update(GameObject* obj) {
    Tower* tower = (Tower*)obj;
    tower->resetDirty();

    DrawParamsTower* dp = new DrawParamsTower();
    if (!constructed_  || tower->getOrientation() != oldRotation_
        || oldFiring_ != firing_ || oldRadius_ != visibleRange_) {
        constructed_ = true;
        oldRotation_ = tower->getOrientation();
        oldFiring_ = firing_;
        oldRadius_ = visibleRange_;

    } else {
        return;
    }
    radius_ = 
        ((TowerPhysicsComponent*) tower->getPhysicsComponent())->getRadius();
    dp->pos     = tower->getPos();
    dp->scale   = 1;
    dp->degrees = tower->getOrientation();
    dp->animate = animate_;
    dp->displayRadius = visibleRange_;



    
    if (hasFiringAnimation_ && firing_) {
        dp->pixmapIdx = 1;
        if (!timerRunning_) { 
            timerID_ = startTimer(reloadTime_);
            timerRunning_ = true;
        }
    } else {
        dp->pixmapIdx = 0;
    }
    constructed_ = true;
    emit signalDraw(dp, this, LAYER_TOWER);
}

void TowerGraphicsComponent::timerEvent(QTimerEvent*) {
    killTimer(timerID_);
    firing_ = false;
    timerRunning_ = false;
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
    setImgIndex(dps->pixmapIdx);
    if (dps->displayRadius) {
        QPointF point = dps->pos;
        rangeCircle_->setRect(point.x()-radius_, point.y()-radius_, 
                              radius_ * 2, radius_ * 2);
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
