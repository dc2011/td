#include "GraphicsComponent.h"
#include <math.h>

QTimer * GraphicsComponent::animationTimer_;
QMutex GraphicsComponent::mutex_;
    
GraphicsComponent::GraphicsComponent() {
    mutex_.lock();
    mainWindow_ = td::MainWindow::instance();
    //td::MainWindow* main = td::MainWindow::instance();
    connect(this, SIGNAL(created(GraphicsComponent*)), 
            mainWindow_, SLOT(createGraphicRepr(GraphicsComponent*)));
    connect(this, SIGNAL(signalDraw(DrawParams*, GraphicsComponent*)), 
            mainWindow_, SLOT(drawItem(DrawParams*, GraphicsComponent*)));
    connect(this, SIGNAL(signalAnimateTick(GraphicsComponent*)),
            mainWindow_, SLOT(animateItem(GraphicsComponent*)));

    if (!animationTimer_) {
        animationTimer_ = new QTimer();
        animationTimer_->start(ANIMATION_TIMEOUT);
    }
    mutex_.unlock();
    create();
}

GraphicsComponent::~GraphicsComponent() {
    delete(pixmapItem_);
    delete(pixmapImgs);

}

void GraphicsComponent::create() {
    emit created(this);
}

void GraphicsComponent::draw(DrawParams* dp) {
    if (pixmapItem_ == NULL) {
        return;
    }
    QPointF center = pixmapItem_->boundingRect().center();
    pixmapItem_->resetMatrix();//important
    pixmapItem_->translate(center.x(), center.y());
    pixmapItem_->setScale(dp->scale);
    pixmapItem_->rotate(dp->degrees * -1);
    pixmapItem_->translate(-center.x(), -center.y());
    pixmapItem_->setPos(dp->pos);
    pixmapItem_->setPos(dp->pos);
    if (dp != NULL) {
        delete dp;
    }
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
    connect(GraphicsComponent::animationTimer_, SIGNAL(timeout()), this, SLOT(onTimerTick()));
}

void GraphicsComponent::animateDisconnect() {
    disconnect(GraphicsComponent::animationTimer_, SIGNAL(timeout()), this, SLOT(onTimerTick()));
}

void GraphicsComponent::animate() {
    //generic this does not animate.
}

void GraphicsComponent::setImgIndex(int index) {
    //if (pixmapItem_ == NULL || pixmapImgs == NULL) {
    //    return;
    //}
    pixmapIndex = index;
    pixmapItem_->setPixmap(pixmapImgs[pixmapIndex]);
}

void GraphicsComponent::onTimerTick() {
    emit signalAnimateTick(this);
}
