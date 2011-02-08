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

    gc->setPixmapItem(pixmap);
}

void MainWindow::drawItem(GraphicsComponent* gc) {
    QGraphicsPixmapItem* itm = gc->getPixmapItem();
    if (itm != NULL) {
        QPixmap pix(100, 100);
        pix.fill(QColor(0, 0, 255));
        itm->setPixmap(pix);
        itm->update();
    }
}

bool MainWindow::event(QEvent* event) {
    QKeyEvent* keyEvent;
    switch (event->type()) {
        case QEvent::ShortcutOverride:
            keyEvent = (QKeyEvent*) event;
            emit signalKeyPressed(keyEvent->key());
            event->accept();
            return true;

        default:
            event->ignore();
            QMainWindow::event(event);
            break;
    }
    
    return true;
}

//void MainWindow::keyPressEvent(QKeyEvent * event) {}

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
