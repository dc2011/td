#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include <QSettings>
#include "../graphics/DrawParams.h"
#include "keymap.h"

/*Bitmask Defines*/
#define KEYUP 1
#define KEYDOWN 2
#define KEYLEFT 4
#define KEYRIGHT 8
#define WINSIZEX 1024
#define WINSIZEY 768

namespace td {

class MapDisplayer;
class GraphicsComponent;

class MainWindow : public QMainWindow {
    Q_OBJECT

private:

    /**
     * The graphics scene which contains all the objects
     */
    QGraphicsScene* scene_;

    /**
     * The view which displays the graphics scene.
     */
    QGraphicsView* view_;
    
    /**
     * The stats menu bar
     */
    QGraphicsTextItem* stats_;

    /**
     * The view which displays the graphics scene.
     */
    QGraphicsRectItem* statsRect_;

    /**
     * The bitmask of keys held and not released
     */
    char keysHeld_;

    /**
     * The keysPressed Timer
     */
    QTimer *keysTimer_;

    /**
     * Tiled map displayer object. Seems to handle parsing and rendering of the
     * tiled map data.
     */
    MapDisplayer * mapDisplayer_;

    /**
     *  Boolean for whether console is open
     */
    bool consoleOpen_;

    /**
     *  Boolean for map being zoomed out
     */
    bool mapZoomOut_;

    /** The keymap defining which keys are bound to which events. */
    Keymap keys_;

public:
    MainWindow();
    virtual ~MainWindow();
    
    QGraphicsScene* getScene() { return scene_; }
    QGraphicsView* getView() { return view_; }

    MapDisplayer * getMD() { return mapDisplayer_; }
    
protected:
    /**
     * Deals with keyboard presses. Arrow keys are handled elsewhere.
     *
     * @author Dean Morin
     * @param event The key press event.
     */
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void keyReleaseEvent(QKeyEvent *);

    void loadKeymap();

public slots:
    /**
     * Calls the graphics objects initfunction
     * Which loads all pixmap images then draws the object
     * offscreen.
     *
     * @author Darryl Pogue
     * @author Warren Voelkl
     * @param gc The GraphicsComponent of the game object.
     */
    void createGraphicRepr(GraphicsComponent* gc);

    /**
     * Removes the graphics item from the scene, and wraps the graphics
     * component in an object so that it'll be deleted after all events related
     * to it are removed from the event queue (ideally).
     *
     * @author Dean Morin
     * @param gc The object to safely delete.
     */
    void removeGraphicRepr(GraphicsComponent* gc);

    /**
     * Draws the graphical representation of the game object.
     *
     * @author Darryl Pogue
     * @param gc The GraphicsComponent of the game object.
     */
    void drawItem(void* dp, GraphicsComponent* gc, int layer);
    
    /**
     * Emits signals depending on the keys held down
     *
     * @author Terence Stenvold
     */
    void keyHeld();

    /**
     * Blatant hack to workaround stupid thread issues.
     *
     * @author Darryl Pogue
     */
    void openWindow() {
        this->show();
    }

    /**
     * Scrolls the window to keep it centered around the provided co-ordinates.
     *
     * @param pos The co-ordinate to center on.
     *
     * @author Tom Nightingale
     */
    void scroll(QPointF pos);

signals:
    void signalKeyPressed(int);
    void signalKeyReleased(int);
    /**
     * The number keys are used to select options from the context menu.
     * 
     * Connected to selectMenuItem() in ContextMenu.cpp.
     *
     * @author Dean Morin
     */
    void signalNumberPressed(int keyPressed);

    /**
     * The spacebar is essentially the 'action' button. Its function depends on
     * what object the player is currently standing on.
     *
     * Connected to handleSpacebarPress() in CDriver.cpp.
     *
     * @author Dean Morin
     */
    void signalSpacebarPressed();

    /**
     * The alt key shows additional info on the screen when held (enemy health,
     * player names, tower building resource requirements, etc.). 
     *
     * Connected to viewResources() in ContextMenu.cpp, and showHealth() in 
     * NPCGraphicsComponent.cpp.
     *
     * @author Dean Morin
     * @param keyHeld True if the alt key is currently being held down.
     */
    void signalAltHeld(bool keyHeld);

    /**
     * Signals that the spacebar has been released.
     *
     * Connected to stopHarvesting() in Player.cpp
     *
     * @author Dean Morin
     */
    void signalSpacebarReleased();
};

} /* end namespace td */

#endif
