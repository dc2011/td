#include "TowerGraphicsComponent.h"
#include <QPointF>
#include <QPainter>
#include <QGradientStops>
#include "../engine/CDriver.h"
#include "../engine/Tower.h"
#include "../physics/TowerPhysicsComponent.h"

namespace td {
    
TowerGraphicsComponent::TowerGraphicsComponent()
        : GraphicsComponent(), levelIndicator_(NULL), 
          levelIndicatorShowing_(false), firing_(false), timerRunning_(false),
          timerID_(0), reloadTime_(0), hasFiringAnimation_(false) {
}

TowerGraphicsComponent::~TowerGraphicsComponent() {
    disconnect();
    delete rangeCircle_;
    delete levelIndicator_;
}

void TowerGraphicsComponent::update(GameObject* obj) {
    Tower* tower = (Tower*)obj;
    tower->resetDirty();

    DrawParamsTower* dp = new DrawParamsTower();
    radius_ = 
        ((TowerPhysicsComponent*) tower->getPhysicsComponent())->getRadius();
    dp->pos     = tower->getPos();
    dp->scale   = 1;
    dp->degrees = tower->getOrientation();
    dp->animate = animate_;
    dp->displayRadius = visibleRange_;
    dp->towerLevel = tower->getLevel();
    
    if (hasFiringAnimation_ && firing_) {
        dp->pixmapIdx = 1;
        if (!timerRunning_) { 
            timerID_ = startTimer(reloadTime_);
            timerRunning_ = true;
        }
    } else {
        dp->pixmapIdx = 0;
    }

    emit signalDraw(dp, this, LAYER_TOWER);
}

void TowerGraphicsComponent::initPixmaps() {
    levelIndicator_ = new QGraphicsPixmapItem();
    levelIndicator_->setZValue(LAYER_TOWER_TRI);
    levelIndicator_->setVisible(false);
    levelIndicator_->setScale(0.75);
    levelIndicator_->setPixmap(PIX_TOWER_LEVEL_TRI);
    CDriver::instance()->getMainWindow()->getScene()->addItem(levelIndicator_);
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
    DrawParamsTower* dps = (DrawParamsTower*) dp;
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

    if (dps->towerLevel == 2 || dps->towerLevel == 4) {
        if (!levelIndicatorShowing_) {
            QPointF pos = dps->pos;
            pos.setX(pos.x() + 8);
            pos.setY(pos.y() - 22);
            levelIndicator_->setPos(pos);
            levelIndicator_->setVisible(true);
            levelIndicator_->update();
            levelIndicatorShowing_ = true;
        }

    } else if (levelIndicatorShowing_) {
        levelIndicator_->setVisible(false);
        levelIndicator_->update();
        levelIndicatorShowing_ = false;
    }

    GraphicsComponent::draw(dp, layer);
}

} /* end namespace td */
