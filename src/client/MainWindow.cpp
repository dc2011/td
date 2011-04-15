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
    
    loadKeymap();
    
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

void MainWindow::loadKeymap() {
    QSettings settings;
    settings.beginGroup("keymap");

    keys_.menuKey = QKeySequence(settings.value("menu", "space").toString());
    keys_.extraInfoKey = QKeySequence(settings.value("extrainfo", "r").toString());
    keys_.consoleKey = QKeySequence(settings.value("console", "`").toString());
    keys_.voiceKey = QKeySequence(settings.value("voice", "v").toString());

    keys_.arrowUp = QKeySequence(settings.value("arrowup", "up").toString());
    keys_.arrowDown = QKeySequence(settings.value("arrowdown", "down").toString());
    keys_.arrowLeft = QKeySequence(settings.value("arrowleft", "left").toString());
    keys_.arrowRight = QKeySequence(settings.value("arrowright", "right").toString());

    settings.endGroup();
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
    PlayerInputComponent *tInput = NULL;
    if(event->isAutoRepeat()) {
        return;
    }

    int mods = event->modifiers();
    QKeySequence key(mods ? mods : event->key(), mods ? event->key() : 0);
    
    if(consoleOpen_ == true) {
        if(event->key() == Qt::Key_Return) {
            Console::instance()->addChar("\n");            
        } else if (event->key() == Qt::Key_Backspace) {
            Console::instance()->removeChar();
        } else if (event->key() >= 32 && event->key() <= 126
                   && event->key() != 96) {
            Console::instance()->addChar(event->text());
        }

        if (keys_.consoleKey.matches(key) == QKeySequence::ExactMatch) {
            Console::instance()->hide();
            consoleOpen_ = !consoleOpen_;
            tInput = (PlayerInputComponent *)CDriver::instance()->
                getHuman()->getInputComponent();
            tInput->playerMovement(true);
        }
        return;
    }
    
    if (keys_.menuKey.matches(key) == QKeySequence::ExactMatch) {
        /* Menu key => Spacebar */
        emit signalSpacebarPressed();
    } else if (keys_.extraInfoKey.matches(key) == QKeySequence::ExactMatch) {
        /* Extra info key => R */
        emit signalAltHeld(true);
    } else if (keys_.consoleKey.matches(key) == QKeySequence::ExactMatch) {
        /* Console key => ~ (tilde) */
        Console::instance()->show();
        consoleOpen_ = !consoleOpen_;
        tInput = (PlayerInputComponent *)CDriver::instance()->
            getHuman()->getInputComponent();
        tInput->playerMovement(false); 
        keysHeld_ = 0;
    } else if (keys_.voiceKey.matches(key) == QKeySequence::ExactMatch) {
        /* Voice key => V */
        // Temporarily disabled
        //AudioManager::instance()->toggleCapturePause();
    } else if (keys_.arrowUp.matches(key) == QKeySequence::ExactMatch) {
        /* Arrow Up key => UP */
        keysHeld_ |= KEYUP;
    } else if (keys_.arrowDown.matches(key) == QKeySequence::ExactMatch) {
        /* Arrow Down key => DOWN */
        keysHeld_ |= KEYDOWN;
    } else if (keys_.arrowLeft.matches(key) == QKeySequence::ExactMatch) {
        /* Arrow Left key => LEFT */
        keysHeld_ |= KEYLEFT;
    } else if (keys_.arrowRight.matches(key) == QKeySequence::ExactMatch) {
        /* Arrow Right key => RIGHT */
        keysHeld_ |= KEYRIGHT;
    } else if (event->key() == Qt::Key_Escape) {
        /* Open the keymap editor => ESC */
        KeymapDialog* km = new KeymapDialog();
        if (km->exec() == QDialog::Accepted) {
            km->savemap();
            loadKeymap();
        }
    } else {
        /* Any other key */
        QMainWindow::keyPressEvent(event);
    }

    switch (event->key()) {
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
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent * event) {

    if(event->isAutoRepeat()) {
        return;
    } else if (consoleOpen_ == true) {
	keysHeld_ = 0;
	return;
    }

    int mods = event->modifiers();
    QKeySequence key(mods ? mods : event->key(), mods ? event->key() : 0);

    if (keys_.menuKey.matches(key) == QKeySequence::ExactMatch) {
        /* Menu key => Spacebar */
        emit signalSpacebarReleased();
    } else if (keys_.extraInfoKey.matches(key) == QKeySequence::ExactMatch) {
        /* Extra info key => R */
        emit signalAltHeld(false);
    } else if (keys_.voiceKey.matches(key) == QKeySequence::ExactMatch) {
        /* Voice key => V */
        // Temporarily disabled
        //AudioManager::instance()->toggleCapturePause();
    } else if (keys_.arrowUp.matches(key) == QKeySequence::ExactMatch) {
        /* Arrow Up key => UP */
        keysHeld_ ^= KEYUP;
        emit signalKeyReleased(Qt::Key_Up);
    } else if (keys_.arrowDown.matches(key) == QKeySequence::ExactMatch) {
        /* Arrow Down key => DOWN */
        keysHeld_ ^= KEYDOWN;
        emit signalKeyReleased(Qt::Key_Down);
    } else if (keys_.arrowLeft.matches(key) == QKeySequence::ExactMatch) {
        /* Arrow Left key => LEFT */
        keysHeld_ ^= KEYLEFT;
        emit signalKeyReleased(Qt::Key_Left);
    } else if (keys_.arrowRight.matches(key) == QKeySequence::ExactMatch) {
        /* Arrow Right key => RIGHT */
        keysHeld_ ^= KEYRIGHT;
        emit signalKeyReleased(Qt::Key_Right);
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::scroll(QPointF pos) {
  //qDebug("MainWindow::scroll(); Player must be moving pos: (%d, %d)", x, y);
  view_->centerOn(pos);
}

} /* end namespace td */
