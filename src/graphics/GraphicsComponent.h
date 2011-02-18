#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <QMutexLocker>
#include <QObject>
#include <QPointF>
#include <QGraphicsPixmapItem>
#include "DrawParams.h"
#include "../client/MainWindow.h"
#include "../engine/GameObject.h"


class GraphicsComponent : public QObject {
    Q_OBJECT

private:
    QGraphicsPixmapItem* pixmapItem_;
    QMutex mutex_;

public:
    /**
     * Sets up the necessary signals and slots to create the 
     * QGraphicsPixmapItem for this component in the rendering thread. This      * is done to ensure that updates on the pixmap item are thread-safe.
     *
     * @author Dean Morin
     */
    GraphicsComponent();

    virtual ~GraphicsComponent() {}
    virtual void update(GameObject* obj) = 0;

    /**
     * Create the object in the graphics context.
     * This emits the created signal with a pointer to the current
     * GraphicsComponent.
     *
     * @author Darryl Pogue
     */
    void create();

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
     * Gets the QGraphicsPixmapItem that represents this object.
     * The return value should be checked for NULL, in case the object has
     * not been created in the graphics context yet.
     *
     * @author Darryl Pogue
     * @author Dean Morin
     * @return The pixmap pointer, or NULL if it has not been initialized.
     */
    QGraphicsPixmapItem* getPixmapItem();

    /**
     * Sets the QGraphicsPixmapItem that represents this object.
     *
     * @author Darryl Pogue
     * @author Dean Morin
     * @param qgpi The QGraphicsPixmapItem to be stored.
     */
    void setPixmapItem(QGraphicsPixmapItem* qgpi);

signals:
    void created(GraphicsComponent* gc);
    void signalDraw(DrawParams* dp, GraphicsComponent* gc);
};

#endif

