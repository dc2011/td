#include "MainWindow.h"
#include <QScrollArea>
#include <QLabel>
#include <QSize>
#include "map.h"
#include "maprenderer.h"
#include "../audio/manager.h"
#include "../graphics/GraphicsComponent.h"
#include "../graphics/MapDisplayer.h"
#include "../graphics/Console.h"
#include "../util/DelayedDelete.h"
#include "../engine/CDriver.h"
#include "../engine/Player.h"
#include "stats.h"

namespace td {

MainWindow::MainWindow() : QMainWindow() {
    scene_ = new QGraphicsScene();
    view_ = new QGraphicsView(scene_);
    stats_ = new Stats();
    stats_->setFixedHeight(22);

    consoleOpen_ = false;
    mapZoomOut_ = false;

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

    QWidget* centre = new QWidget(this);
    QVBoxLayout* bl = new QVBoxLayout(centre);
    bl->addWidget(stats_);
    bl->addWidget(view_);
    bl->setMargin(0);
    bl->setSpacing(0);

    this->setCentralWidget(centre);
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

void MainWindow::drawItem(void* dp, GraphicsComponent* gc, int layer) {
    gc->draw(dp,layer);
}

void MainWindow::loadKeymap() {
    QSettings settings;
    settings.beginGroup("keymap");

    keys_.choice1Key = QKeySequence(settings.value("choice1", "1").toString());
    keys_.choice2Key = QKeySequence(settings.value("choice2", "2").toString());
    keys_.choice3Key = QKeySequence(settings.value("choice3", "3").toString());
    keys_.choice4Key = QKeySequence(settings.value("choice4", "4").toString());
    keys_.choice5Key = QKeySequence(settings.value("choice5", "5").toString());
    keys_.choice6Key = QKeySequence(settings.value("choice6", "6").toString());
    keys_.choice7Key = QKeySequence(settings.value("choice7", "7").toString());
    keys_.choice8Key = QKeySequence(settings.value("choice8", "8").toString());
    keys_.choice9Key = QKeySequence(settings.value("choice9", "9").toString());

    keys_.menuKey = QKeySequence(settings.value("menu", "space").toString());
    keys_.extraInfoKey = QKeySequence(settings.value("extrainfo", "r").toString());
    keys_.consoleKey = QKeySequence(settings.value("console", "`").toString());
    keys_.voiceKey = QKeySequence(settings.value("voice", "v").toString());
    keys_.zoomKey = QKeySequence(settings.value("zoom", "z").toString());

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
    
    if(consoleOpen_) {
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
        if(!mapZoomOut_) {
            Console::instance()->show();
            consoleOpen_ = !consoleOpen_;
            tInput = (PlayerInputComponent *)CDriver::instance()->
                getHuman()->getInputComponent();
            tInput->playerMovement(false); 
            keysHeld_ = 0;
        }
    } else if (keys_.voiceKey.matches(key) == QKeySequence::ExactMatch) {
        /* Voice key => V */
        // Temporarily disabled
        AudioManager::instance()->toggleCapturePause();
    } else if (keys_.zoomKey.matches(key) == QKeySequence::ExactMatch) {
        /* Zoom key => Z */
        if(mapZoomOut_ == false && 
           view_->sceneRect().toRect().contains(view_->frameRect(),false)) {
	    view_->fitInView(view_->sceneRect().toRect());
            mapZoomOut_ = !mapZoomOut_;
        }
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
    } else if (keys_.choice1Key.matches(key) == QKeySequence::ExactMatch) {
        /* Choice 1 key => 1 */
        emit signalNumberPressed(Qt::Key_1);
    } else if (keys_.choice2Key.matches(key) == QKeySequence::ExactMatch) {
        /* Choice 2 key => 2 */
        emit signalNumberPressed(Qt::Key_2);
    } else if (keys_.choice3Key.matches(key) == QKeySequence::ExactMatch) {
        /* Choice 3 key => 3 */
        emit signalNumberPressed(Qt::Key_3);
    } else if (keys_.choice4Key.matches(key) == QKeySequence::ExactMatch) {
        /* Choice 4 key => 4 */
        emit signalNumberPressed(Qt::Key_4);
    } else if (keys_.choice5Key.matches(key) == QKeySequence::ExactMatch) {
        /* Choice 5 key => 5 */
        emit signalNumberPressed(Qt::Key_5);
    } else if (keys_.choice6Key.matches(key) == QKeySequence::ExactMatch) {
        /* Choice 6 key => 6 */
        emit signalNumberPressed(Qt::Key_6);
    } else if (keys_.choice7Key.matches(key) == QKeySequence::ExactMatch) {
        /* Choice 7 key => 7 */
        emit signalNumberPressed(Qt::Key_7);
    } else if (keys_.choice8Key.matches(key) == QKeySequence::ExactMatch) {
        /* Choice 8 key => 8 */
        emit signalNumberPressed(Qt::Key_8);
    } else if (keys_.choice9Key.matches(key) == QKeySequence::ExactMatch) {
        /* Choice 9 key => 9 */
        emit signalNumberPressed(Qt::Key_9);
    } else {
        /* Any other key */
        QMainWindow::keyPressEvent(event);
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
        AudioManager::instance()->toggleCapturePause();
    } else if (keys_.zoomKey.matches(key) == QKeySequence::ExactMatch) {
        /* Zoom key => Z */
        if(mapZoomOut_ == true && 
           view_->sceneRect().toRect().contains(view_->frameRect(),false)) {
            view_->resetMatrix();
            mapZoomOut_ = !mapZoomOut_;
        }
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
    } else if (event->key() == Qt::Key_Escape) {
        /* Open the mainmenu editor => ESC */
        emit signalShowMainMenu();

    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::scroll(QPointF pos) {
    view_->centerOn(pos);
}

void MainWindow::setMap(QString mapname) {
    mapDisplayer_->viewMap(mapname);
    Tiled::MapRenderer* mRenderer = mapDisplayer_->getMRenderer();
    QSize mapSize = mRenderer->mapSize();
    scene_->setSceneRect(0,0,mapSize.width(), mapSize.height());

    semMap_.release();
}

void MainWindow::endGameCleanup() {
    close();
}

} /* end namespace td */
