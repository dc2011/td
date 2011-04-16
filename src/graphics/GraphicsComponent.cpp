#include "GraphicsComponent.h"
#include <math.h>
#include "../engine/GameObject.h"
#include "../engine/CDriver.h"
#include "../util/DelayedDelete.h"

namespace td {

GraphicsComponent::GraphicsComponent() 
        : pixmapIndex_(0), isMoving_(false), animate_(false) {

#ifndef SERVER    
    MainWindow* mainWindow = CDriver::instance()->getMainWindow();

    connect(this, SIGNAL(created(GraphicsComponent*)), 
            mainWindow, SLOT(createGraphicRepr(GraphicsComponent*)));
    connect(this, SIGNAL(signalDraw(void*, GraphicsComponent*, int)),
            mainWindow, SLOT(drawItem(void*, GraphicsComponent*, int)));
    connect(this, SIGNAL(removeGraphicsItem(GraphicsComponent*)),
            mainWindow, SLOT(removeGraphicRepr(GraphicsComponent*)));
#endif
}

GraphicsComponent::~GraphicsComponent() {
    delete pixmapItem_;
}

void GraphicsComponent::deleteComponent() {
    emit removeGraphicsItem(this);
}

void GraphicsComponent::draw(void* dp, int layer) {
    DrawParams* drawParams = (DrawParams*) dp;
    if (drawParams->animate) {
        animate();
    }

    QPointF center = pixmapItem_->boundingRect().center();
    pixmapItem_->resetMatrix();
    pixmapItem_->setTransformOriginPoint(center);
    pixmapItem_->setScale(drawParams->scale);
    pixmapItem_->rotate(-drawParams->degrees);

    pixmapItem_->translate(-center.x(), -center.y());
    pixmapItem_->setPos(drawParams->pos);
    pixmapItem_->setZValue(layer);
    delete drawParams;

    pixmapItem_->update();
}

QGraphicsPixmapItem* GraphicsComponent::initGraphicsComponent() {
    
    pixmapItem_ = new QGraphicsPixmapItem();
    initPixmaps();
    
    pixmapItem_->setPixmap(getPixmapArray()[pixmapIndex_]);
    pixmapItem_->setPos(OFFSCREEN,OFFSCREEN);

    return pixmapItem_;
}

void GraphicsComponent::setImgIndex(int index) {
    pixmapIndex_ = index;
    pixmapItem_->setPixmap(getPixmapArray()[pixmapIndex_]);
}

} /* end namespace td */
