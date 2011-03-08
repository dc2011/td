#include "GraphicsComponent.h"
#include <math.h>
#include "../engine/GameObject.h"
#include "../engine/CDriver.h"

namespace td {

QMutex GraphicsComponent::mutex_;
    
GraphicsComponent::GraphicsComponent() {
    
    mainWindow_ = td::MainWindow::instance();
    //td::MainWindow* main = td::MainWindow::instance();
    connect(this, SIGNAL(created(GraphicsComponent*)), 
            mainWindow_, SLOT(createGraphicRepr(GraphicsComponent*)));
    connect(this, SIGNAL(signalDraw(DrawParams*, GraphicsComponent*)), 
            mainWindow_, SLOT(drawItem(DrawParams*, GraphicsComponent*)));
    connect(this, SIGNAL(signalAnimateTick(GraphicsComponent*)),
            mainWindow_, SLOT(animateItem(GraphicsComponent*)));

    isMoving_ = 0;
}

GraphicsComponent::~GraphicsComponent() {
    delete(pixmapItem_);
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

}

QPixmap GraphicsComponent::getCurrentPixmap() {
    return pixmapImgs[pixmapIndex];
}

QGraphicsPixmapItem* GraphicsComponent::initGraphicsComponent() {
    mutex_.lock();
    initPixmaps();
    pixmapItem_ = new QGraphicsPixmapItem(pixmapImgs[pixmapIndex]);
    pixmapItem_->setPos(OFFSCREEN,OFFSCREEN);
    mutex_.unlock();
    return pixmapItem_;
}

void GraphicsComponent::animateConnect() {
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
    pixmapIndex = index;
    pixmapItem_->setPixmap(pixmapImgs[pixmapIndex]);
    mutex_.unlock();
}

void GraphicsComponent::onTimerTick() {
    emit signalAnimateTick(this);
}

} /* end namespace td */
