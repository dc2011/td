#include "MainWindow.h"
#include <QScrollArea>
#include <QLabel>
#include <QSize>
#include "map.h"
#include "maprenderer.h"
#include "../audio/manager.h"
#include "../graphics/GraphicsComponent.h"
#include "../graphics/MapDisplayer.h"
#include "../util/DelayedDelete.h"
#include "../graphics/Console.h"
#include "../engine/CDriver.h"
#include "../engine/Player.h"

namespace td {

MainWindow::MainWindow() : QMainWindow() {
    scene_ = new QGraphicsScene();
    view_ = new QGraphicsView(scene_);
    stats_ = new QGraphicsTextItem();
    statsRect_ = new QGraphicsRectItem();

    consoleOpen_ = false;

    scene_->setItemIndexMethod(QGraphicsScene::NoIndex);
    keysHeld_ = 0;
    keysTimer_ = new QTimer(this);
    keysTimer_->start(50);

    view_->setCacheMode(QGraphicsView::CacheBackground);
    view_->setFocusPolicy( Qt::NoFocus );
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->releaseKeyboard();

    //MapDisplayer * mapDisplayer_ = NULL;
    mapDisplayer_ = new MapDisplayer(scene_);
    mapDisplayer_->viewMap(MAP_TMX);
    Tiled::MapRenderer* mRenderer = mapDisplayer_->getMRenderer();
    QSize mapSize = mRenderer->mapSize();

    //Status bar
    statsRect_->setRect(500,0,500,30);
    statsRect_->setBrush(QBrush(QColor(0,0,0)));
    statsRect_->setPen(QPen(QColor(0,0,0)));
    statsRect_->setZValue(98);
    statsRect_->setOpacity(0.8);

    stats_->setDefaultTextColor(QColor(200,200,0));
    stats_->setPos(505,0);
    stats_->setZValue(99);
    stats_->setPlainText("|i|Base Health: 100% |i| Gems: 10 |i| NPC WAVE 0:10s");
    stats_->update();

    scene_->addItem(statsRect_);
    scene_->addItem(stats_);
    this->setCentralWidget(view_);
    scene_->setSceneRect(0,0,mapSize.width(), mapSize.height());
    //view_->setFixedSize(mapSize.width(), mapSize.height());
    //this->showFullScreen();
    
    // This focus policy may be implied by default...
    this->setFocusPolicy(Qt::StrongFocus);

    connect(keysTimer_, SIGNAL(timeout()), this, SLOT(keyHeld()));
}

MainWindow::~MainWindow() {
    /* driver_.shutdown() or something */
}

void MainWindow::createGraphicRepr(GraphicsComponent* gc) {
    scene_->addItem(gc->initGraphicsComponent());
}

void MainWindow::removeGraphicRepr(GraphicsComponent* gc) {
    scene_->removeItem(gc->getPixmapItem());
    new DelayedDelete<GraphicsComponent>(gc);
}

void MainWindow::drawItem(DrawParams* dp, GraphicsComponent* gc, int layer) {
    gc->draw(dp,layer);
}

void MainWindow::keyHeld()
{

    if(keysHeld_ & KEYUP && keysHeld_ & KEYDOWN) {
        emit signalKeyReleased(Qt::Key_Up);
        emit signalKeyReleased(Qt::Key_Down);
        return;
    } else if(keysHeld_ & KEYLEFT && keysHeld_ & KEYRIGHT) {
        emit signalKeyReleased(Qt::Key_Left);
        emit signalKeyReleased(Qt::Key_Right);
        return;
    }

    if(keysHeld_ & KEYUP) {
        emit signalKeyPressed(Qt::Key_Up);
    }
    if(keysHeld_ & KEYDOWN) {
        emit signalKeyPressed(Qt::Key_Down);
    }
    if(keysHeld_ & KEYLEFT) {
        emit signalKeyPressed(Qt::Key_Left);
    }
    if(keysHeld_ & KEYRIGHT) {
        emit signalKeyPressed(Qt::Key_Right);
    }
}

void MainWindow::keyPressEvent(QKeyEvent * event) {
    PlayerInputComponent *tInput;
    
    if(event->isAutoRepeat()) {
        return;
    }
    
    if(consoleOpen_ == true) {
        if(event->key() == Qt::Key_Return) {
            Console::instance()->addChar("\n");            
        } else if (event->key() == Qt::Key_Backspace) {
            Console::instance()->removeChar();
        } else if (event->key() >= 32 && event->key() <= 126
                   && event->key() != 96) {
            Console::instance()->addChar(event->text());
        }

        if (event->key() == 96) {
            Console::instance()->hide();
            consoleOpen_ = !consoleOpen_;
            tInput = (PlayerInputComponent *)CDriver::instance()->
                getHuman()->getInputComponent();
            tInput->playerMovement(true);
        }
        return;
    }
    
    switch (event->key()) {

        case Qt::Key_Space:
            emit signalSpacebarPressed();
            break;
        case Qt::Key_R:
            emit signalAltHeld(true);
            break;
        case Qt::Key_V:
            //AudioManager::instance()->toggleCapturePause();
            break;
        case Qt::Key_Z:    
	    view_->scale(.5,.5);
	    break;
        case Qt::Key_QuoteLeft :
            Console::instance()->show();
            consoleOpen_ = !consoleOpen_;
            tInput = (PlayerInputComponent *)CDriver::instance()->
                getHuman()->getInputComponent();
            tInput->playerMovement(false); 
	    keysHeld_ = 0;
	    break;
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
        case Qt::Key_0:
            emit signalNumberPressed(event->key());
            break;

        case Qt::Key_Up:
            keysHeld_ |= KEYUP;
            break;
        case Qt::Key_Down:
            keysHeld_ |= KEYDOWN;
            break;
        case Qt::Key_Left:
            keysHeld_ |= KEYLEFT;
            break;
        case Qt::Key_Right:
            keysHeld_ |= KEYRIGHT;
            break;

        default:
            QMainWindow::keyPressEvent(event);
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent * event) {

    if(event->isAutoRepeat()) {
        return;
    } else if (consoleOpen_ == true) {
	keysHeld_ = 0;
	return;
    }
    
    switch (event->key()) {

        case Qt::Key_Up:
            keysHeld_ ^= KEYUP;
            emit signalKeyReleased(event->key());
            break;
        case Qt::Key_Down:
            keysHeld_ ^= KEYDOWN;
            emit signalKeyReleased(event->key());
            break;
        case Qt::Key_Left:
            keysHeld_ ^= KEYLEFT;
            emit signalKeyReleased(event->key());
            break;
        case Qt::Key_Right:
            keysHeld_ ^= KEYRIGHT;
            emit signalKeyReleased(event->key());
            break;
        case Qt::Key_R:
            emit signalAltHeld(false);
            break;
        case Qt::Key_V:
            //AudioManager::instance()->toggleCapturePause();
            break;
        case Qt::Key_Z:
            view_->scale(2,2);
            break;
        case Qt::Key_Space:
            emit signalSpacebarReleased();
            break;
        default:
            QMainWindow::keyPressEvent(event);
            break;
    }
}

void MainWindow::scroll(QPointF pos) {
  //qDebug("MainWindow::scroll(); Player must be moving pos: (%d, %d)", x, y);
  view_->centerOn(pos);
}

} /* end namespace td */
