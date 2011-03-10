#include "GraphicsComponent.h"
#include <math.h>
#include "../engine/GameObject.h"
#include "../engine/CDriver.h"
#include "../util/DelayedDelete.h"

namespace td {

QMutex GraphicsComponent::mutex_;
    
GraphicsComponent::GraphicsComponent() {
    
    MainWindow* mainWindow = CDriver::instance()->getMainWindow();

    connect(this, SIGNAL(created(GraphicsComponent*)), 
            mainWindow, SLOT(createGraphicRepr(GraphicsComponent*)));
    connect(this, SIGNAL(signalDraw(DrawParams*, GraphicsComponent*, int)), 
            mainWindow, SLOT(drawItem(DrawParams*, GraphicsComponent*, int)));
    connect(this, SIGNAL(signalAnimateTick(GraphicsComponent*)),
            mainWindow, SLOT(animateItem(GraphicsComponent*)));

    isMoving_ = 0;
}

GraphicsComponent::~GraphicsComponent() {
    disconnect(this, SLOT(onTimerTick()));
    new DelayedDelete<QGraphicsPixmapItem>(pixmapItem_);
}

void GraphicsComponent::create() {
    emit created(this);
}

void GraphicsComponent::draw(DrawParams* dp, int layer) {
    QPointF center = pixmapItem_->boundingRect().center();
    pixmapItem_->resetMatrix();//important
    //pixmapItem_->translate(center.x(), center.y());
    pixmapItem_->setTransformOriginPoint(center);
    pixmapItem_->setScale(dp->scale);
    pixmapItem_->rotate(dp->degrees * -1);
    pixmapItem_->translate(-center.x(), -center.y());
    //pixmapItem_->setTransformOriginPoint(-center.x(), -center.y());
    pixmapItem_->setPos(dp->pos);
    pixmapItem_->setZValue(layer);
    isMoving_ = dp->moving;
    delete dp;

    pixmapItem_->update();
}

QPixmap GraphicsComponent::getCurrentPixmap() {
    return pixmapImgs_[pixmapIndex_];
}

QGraphicsPixmapItem* GraphicsComponent::initGraphicsComponent() {
    mutex_.lock();
    initPixmaps();
    pixmapItem_ = new QGraphicsPixmapItem(pixmapImgs_[pixmapIndex_]);
    pixmapItem_->setPos(OFFSCREEN,OFFSCREEN);
    mutex_.unlock();
    return pixmapItem_;
}

void GraphicsComponent::animateConnect() {
    return;
    connect(CDriver::getTimer(),
            SIGNAL(timeout()), this, SLOT(onTimerTick()));
}

void GraphicsComponent::animateDisconnect() {
    disconnect(CDriver::getTimer(),
               SIGNAL(timeout()), this, SLOT(onTimerTick()));
}

void GraphicsComponent::animate() {
    //generic this does not animate.
}

void GraphicsComponent::setImgIndex(int index) {
    mutex_.lock();
    pixmapIndex_ = index;
    pixmapItem_->setPixmap(pixmapImgs_[pixmapIndex_]);
    mutex_.unlock();
}

void GraphicsComponent::onTimerTick() {
    emit signalAnimateTick(this);
}

} /* end namespace td */
