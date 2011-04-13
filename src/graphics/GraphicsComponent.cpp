#include "GraphicsComponent.h"
#include <math.h>
#include "../engine/GameObject.h"
#include "../engine/CDriver.h"
#include "../util/DelayedDelete.h"
#include <QDebug>

namespace td {

GraphicsComponent::GraphicsComponent() 
        : pixmapIndex_(0), isMoving_(false), animate_(true) {

#ifndef SERVER    
    MainWindow* mainWindow = CDriver::instance()->getMainWindow();

    connect(this, SIGNAL(created(GraphicsComponent*)), 
            mainWindow, SLOT(createGraphicRepr(GraphicsComponent*)));
    connect(this, SIGNAL(signalDraw(DrawParams*, GraphicsComponent*, int)), 
            mainWindow, SLOT(drawItem(DrawParams*, GraphicsComponent*, int)));
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

//gotta be a better way to do these two functions but this is quicker than thinking
void GraphicsComponent::setCurrentResource(int) {
    qDebug() << "if you reach this you are doing something stupid";
}

void GraphicsComponent::setBuildingResources(int, int) {
    qDebug() << "if you reach this you are doing something stupid";
}

void GraphicsComponent::setBuildingStage(int) {
    qDebug() << "I really need to cleanup these hacks";
}

} /* end namespace td */
QPixmap * getPixmapArray() {
    return 0;
}
