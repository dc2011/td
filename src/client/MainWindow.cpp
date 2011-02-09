#include "MainWindow.h"
#include "graphics/mapdisplayer.h"
#include <QScrollArea>

namespace td {

MainWindow::MainWindow() : QMainWindow() {
    scene_ = new QGraphicsScene();
    view_ = new QGraphicsView(scene_);

    MapDisplayer* map = new MapDisplayer(scene_);

    map->viewMap(QString("../maps/desert.tmx"));

    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScrollArea *a = new QScrollArea(this);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);    
    this->setCentralWidget(view_);
    this->showFullScreen();
    view_->setFixedSize(1024,768);
}

MainWindow::~MainWindow() {
    /* driver_.shutdown() or something */
}

void MainWindow::createGraphicRepr(GraphicsComponent* gc) {
    QGraphicsPixmapItem* pixmap = new QGraphicsPixmapItem();
    scene_->addItem(pixmap);

    gc->setPixmapItem(pixmap);
}

void MainWindow::drawItem(QPoint pos, GraphicsComponent* gc) {    
    gc->draw(&pos);
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
