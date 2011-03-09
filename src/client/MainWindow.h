#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include "../graphics/DrawParams.h"

/*Bitmask Defines*/
#define KEYUP 1
#define KEYDOWN 2
#define KEYLEFT 4
#define KEYRIGHT 8

namespace td {

class MapDisplayer;
class GraphicsComponent;

class MainWindow : public QMainWindow {
    Q_OBJECT

private:

    MainWindow();
    virtual ~MainWindow();
    
    /**
     * The single instance of this class that can be created.
     */
    static MainWindow* instance_;
    
    /**
     * The graphics scene which contains all the objects
     */
    QGraphicsScene* scene_;

    /**
     * The view which displays the graphics scene.
     */
    QGraphicsView* view_;

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

public:
    /**
     * Creates an instance of the class if one doesn't exist yet.
     *
     * @author Dean Morin
     * @returns An new instance of the class if one doesn't exist yet, or
     * if one does, it returns a pointer to that instance.
     */
    static MainWindow* init();
   
    /**
     * Returns the instance of this Singleton class. Should only be used if
     * you know that init() has already been called.
     *
     * @author Dean Morin
     * @returns A pointer to the one available instance of this class.
     */
    static MainWindow* instance() {
        return instance_;
    }
    
    QGraphicsScene* getScene() { return scene_; }

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
     * Draws the graphical representation of the game object.
     *
     * @author Darryl Pogue
     * @param gc The GraphicsComponent of the game object.
     */
    void drawItem(DrawParams* dp, GraphicsComponent* gc, int layer);
    void animateItem(GraphicsComponent* gc);
    
    /**
     * Emits signals depending on the keys held down
     *
     * @author Terence Stenvold
     */
    void keyHeld();

signals:
    void signalKeyPressed(int);
    void signalKeyReleased(int);
    void signalNumberPressed(int);
    void signalSpacebarPressed();
    void signalRHeld(bool);
    void signalFPressed();
};

} /* end namespace td */

#endif
