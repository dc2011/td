#include "GraphicsComponent.h"
    
GraphicsComponent::GraphicsComponent() {
    td::MainWindow* main = td::MainWindow::instance();
    connect(this, SIGNAL(created(GraphicsComponent*)), 
            main, SLOT(createGraphicRepr(GraphicsComponent*)));
    connect(this, SIGNAL(signalDraw(DrawParams*, GraphicsComponent*)), 
            main, SLOT(drawItem(DrawParams*, GraphicsComponent*)));
    create();
}

void GraphicsComponent::create() {
    emit created(this);
}

QGraphicsPixmapItem* GraphicsComponent::getPixmapItem() { 
    QGraphicsPixmapItem* ret;

    mutex_.lock();
    ret = pixmapItem_;
    mutex_.unlock();

    return ret;
}

void GraphicsComponent::setPixmapItem(QGraphicsPixmapItem* qgpi) {
    mutex_.lock();
    pixmapItem_ = qgpi;
    mutex_.unlock();
}

void GraphicsComponent::draw(DrawParams* dp) {
    QGraphicsPixmapItem* itm = getPixmapItem();
    QPointF center;
    
    if (itm != NULL) {
        itm->setPixmap(getCurrentPixmap());
    }
    center = itm->boundingRect().center();
    itm->resetMatrix();//important
    itm->setPos(dp->pos);
    itm->translate(center.x(), center.y());
    itm->setScale(1);
    itm->rotate(dp->degrees);
    itm->translate(-center.x(), -center.y());
    if (dp != NULL) {
        delete dp;
    }
}

