#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#define OFFSCREEN -10000

#include <QMutexLocker>
#include <QObject>
#include <QPointF>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "DrawParams.h"
#include "PixmapFiles.h"
#include "../client/MainWindow.h"
#include "../util/mutex_magic.h"

namespace td {

class GameObject;

class GraphicsComponent : public QObject {
    Q_OBJECT
    THREAD_SAFE_SINGLETON

private:
    /**
     *  the pixelmapItem which is is used to draw a pixel map at a location
     **/
    QGraphicsPixmapItem* pixmapItem_;
    
    /**
     * Pointer to the mainwindow
     */
    MainWindow* mainWindow_;

protected:
    /**
     * If the obect is currently moving used for animations
     */
    bool isMoving_;
    /**
     * container for all pixmaps
     **/
    QPixmap * pixmapImgs;

    /**
     * the current index for the currently drawn pixmap
     **/
    int pixmapIndex;

    /**
     * updates the img index
     * @author Warren Voelkl
     **/
    void setImgIndex(int index);

    /**
     * Creates a connection between the timer and this object
     * @author Warren Voelkl / Terence Stenvold
     **/
    void animateConnect();

    /**
     * Disconnect the connection between the timer this object
     * @author Warren Voelkl / Terence Stenvold
     **/
    void animateDisconnect();

    /**
     * Create the object in the graphics context.
     * This emits the created signal with a pointer to the current
     * GraphicsComponent.
     *
     * @author Darryl Pogue
     */
    void create();

public:
    /**
     * This generic class does  not need to be implemented if there are no animations
     * This is were all animation logic will be implemented
     * @author Warren Voelkl
     */

    virtual void animate();
    /**
     * Sets up the necessary signals and slots to create the 
     * QGraphicsPixmapItem for this component in the rendering thread. This
     * is done to ensure that updates on the pixmap item are thread-safe.
     *
     * @author Dean Morin, Warren Voelkl
     */
    GraphicsComponent();

    virtual ~GraphicsComponent();

    /**
     * TODO for each GraphicsComponensts update function
     * 1. check for dirty value
     * 2. Instantiate DrawParams structure
     * 3. load only the modifiable values of structure rest will be set to a default.
     * @author Warren Voelkl
     */
    virtual void update(GameObject* obj) = 0;

    /**
     * Resets the matrix then builds the transformation matrix from the
     * structure values.
     *
     * @author warren
     * @param Pointer to the drawstruct that contains all the values on how
     * to render an image.
     */
    void draw(DrawParams* dp);

    /**
     * Called from main. instantiates the QGRaphicsPixmapItem
     * @author Warren Voelkl
     */
    QGraphicsPixmapItem* initGraphicsComponent();

    /**
     * the function where the pixmap container is loaded
     * called on construction of the object but not in the constructor
     * @author Warren Voelkl
     */
    virtual void initPixmaps() = 0;

    /**
     * returns the current pixmap image pointed to from the pixmapimg
     * @author Warren Voelkl
     */
    QPixmap getCurrentPixmap();

public slots:
    /**
     * emits a signal to the gui thread when a timer has ticked
     * @author Warren Voelkl
     */
    void onTimerTick();

signals:
    void created(GraphicsComponent* gc);
    void signalDraw(DrawParams* dp, GraphicsComponent* gc);
    void signalAnimateTick(GraphicsComponent * gc);
};

} /* end namespace td */

#endif
