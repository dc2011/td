#include "GraphicsComponent.h"
#include <math.h>

    
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
    //double pi = 3.14;
    //double a = pi/180 * 10;
    //double sina = sin(a);
    //double cosa = cos(a);
    //QPixmap pixmap = pixmapItem_->pixmap();
    //int xcenter =pixmap.width();
    //int ycenter =pixmap.height();
    QPointF center = pixmapItem_->boundingRect().center();

    //pixmap.scaled(QSize(dp->scale, dp->scale), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //QMatrix translationMatrix(1, 0, 0, 1, xcenter, ycenter);
    //QMatrix rotationMatrix(cosa, -sina, sina, cosa, 0, 0)t;
    //QMatrix scalingMatrix(1.1, 0, 0, 1.1, 0, 0);
    //QMatrix matrix;
    //matrix.translate(-xcenter, -ycenter);
    //matrix = matrix * scalingMatrix;
    //matrix =  translationMatrix * scalingMatrix * QMatrix(1, 0, 0, 1, -xcenter, -ycenter);
    //matrix = matrix.translate(pixmap.width() / 2,pixmap.height() / 2);
    //matrix = matrix.scale(dp->scale, dp->scale);
    //matrix = matrix.rotate(dp->degrees);
    //matrix = matrix.translate(-pixmap.width() / 2, - pixmap.height() / 2 );
    //pixmap = pixmap.transformed(scalingMatrix, Qt::SmoothTransformation);
            //.transforme(transform.rotate(dp->degrees,Qt::XAxis ), Qt::SmoothTransformation);
    //center = pixmapItem_->boundingRect().center();


    pixmapItem_->resetMatrix();//important
    pixmapItem_->translate(center.x(), center.y());
    pixmapItem_->setScale(dp->scale);
    pixmapItem_->rotate(dp->degrees * -1);
    pixmapItem_->translate(-center.x(), -center.y());
    pixmapItem_->setPos(dp->pos);

    //pixmapItem_->setPixmap(newPixmap);

    //pixmapItem_->setPixmap(pixmap);

    pixmapItem_->setPos(dp->pos);
    if (dp != NULL) {
        delete dp;
    }
}

QPixmap GraphicsComponent::getCurrentPixmap() {
    return pixmapImgs[pixmapIndex];
}

void GraphicsComponent::initGraphicsComponent() {
    initPixmaps();
    mutex_.lock();
    pixmapItem_ = new QGraphicsPixmapItem(pixmapImgs[pixmapIndex]);
    mutex_.unlock();
}
