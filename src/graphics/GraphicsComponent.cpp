#include "GraphicsComponent.h"
#include <math.h>
#include "../engine/GameObject.h"
#include "../engine/CDriver.h"
#include "../util/DelayedDelete.h"

namespace td {

//QMutex GraphicsComponent::mutex_;
    
GraphicsComponent::GraphicsComponent() : pixmapIndex_(0) {

    MainWindow* mainWindow = CDriver::instance()->getMainWindow();

    connect(this, SIGNAL(created(GraphicsComponent*)), 
            mainWindow, SLOT(createGraphicRepr(GraphicsComponent*)));
    connect(this, SIGNAL(signalDraw(DrawParams*, GraphicsComponent*, int)), 
            mainWindow, SLOT(drawItem(DrawParams*, GraphicsComponent*, int)));
    connect(this, SIGNAL(removeGraphicsItem(GraphicsComponent*)),
            mainWindow, SLOT(removeGraphicRepr(GraphicsComponent*)));

    isMoving_ = 0;
    animate_ = true;
}

GraphicsComponent::~GraphicsComponent() {
    delete pixmapItem_;
}

void GraphicsComponent::deleteComponent() {
    emit removeGraphicsItem(this);
}

void GraphicsComponent::draw(DrawParams* dp, int layer) {

    if (animate_) {
        animate();
    }

    QPointF center = pixmapItem_->boundingRect().center();
    pixmapItem_->resetMatrix();//important
    pixmapItem_->setTransformOriginPoint(center);
    pixmapItem_->setScale(dp->scale);
    pixmapItem_->rotate(-dp->degrees);

    pixmapItem_->translate(-center.x(), -center.y());
    pixmapItem_->setPos(dp->pos);
    pixmapItem_->setZValue(layer);
    isMoving_ = dp->moving;
    delete dp;

    pixmapItem_->update();
}

QGraphicsPixmapItem* GraphicsComponent::initGraphicsComponent() {
    
    //mutex_.lock();
    pixmapItem_ = new QGraphicsPixmapItem();
    initPixmaps();
    
    pixmapItem_->setPixmap(getPixmapArray()[pixmapIndex_]);
    pixmapItem_->setPos(OFFSCREEN,OFFSCREEN);

    //mutex_.unlock();
    return pixmapItem_;
}

void GraphicsComponent::setImgIndex(int index) {
    
    //mutex_.lock();
    pixmapIndex_ = index;
    pixmapItem_->setPixmap(getPixmapArray()[pixmapIndex_]);
    //mutex_.unlock();
}

} /* end namespace td */
QPixmap * getPixmapArray() {
    return 0;
}
