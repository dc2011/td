#include "MainWindow.h"

namespace td {

MainWindow::MainWindow() : QMainWindow() {
    scene_ = new QGraphicsScene();
    view_ = new QGraphicsView(scene_);

    this->setCentralWidget(view_);
}

MainWindow::~MainWindow() {
    /* driver_.shutdown() or something */
}

void MainWindow::createGraphicRepr(GraphicsComponent* gc) {
    QGraphicsPixmapItem* pixmap = new QGraphicsPixmapItem();
    scene_->addItem(pixmap);

    //gc->setPixmap(pixmap);
}

void MainWindow::keyPressEvent(QKeyEvent * event) {
    switch (event->key()) {
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Left:
        case Qt::Key_Right:
            qDebug("MainWindow::keyPressEvent;");
            emit signalKeyPressed(event->key());
            break;
            
        default:
            QMainWindow::keyPressEvent(event);
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent * event) {
    switch (event->key()) {
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Left:
        case Qt::Key_Right:
            //qDebug("MainWindow::keyReleaseEvent");
            emit signalKeyReleased(event->key());
            break;

        default:
            QMainWindow::keyPressEvent(event);
            break;
    }
}

} /* end namespace td */