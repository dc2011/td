#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <QMutexLocker>
#include <QObject>
#include <QPointF>
#include <QGraphicsPixmapItem>
#include "GameObject.h"

#include "../client/MainWindow.h"

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
    GraphicsComponent() {
        td::MainWindow* main = td::MainWindow::instance();
        connect(this, SIGNAL(created(GraphicsComponent*)), 
                main, SLOT(createGraphicRepr(GraphicsComponent*)));
        connect(this, SIGNAL(signalDraw(QPointF, GraphicsComponent*)), 
                main, SLOT(drawItem(QPointF, GraphicsComponent*)));
        create();
    }

    virtual ~GraphicsComponent() {}
    virtual void update(GameObject* obj) = 0;

    /**
     * Create the object in the graphics context.
     * This emits the created signal with a pointer to the current
     * GraphicsComponent.
     *
     * @author Darryl Pogue
     */
    void create() {
        emit created(this);
    }

    virtual void draw(QPointF* pos) = 0;

    /**
     * Gets the QGraphicsPixmapItem that represents this object.
     * The return value should be checked for NULL, in case the object has
     * not been created in the graphics context yet.
     *
     * @author Darryl Pogue
     * @author Dean Morin
     * @return The pixmap pointer, or NULL if it has not been initialized.
     */
    QGraphicsPixmapItem* getPixmapItem() { 
        QGraphicsPixmapItem* ret;

        mutex_.lock();
        ret = pixmapItem_;
        mutex_.unlock();

        return ret;
    }

    /**
     * Sets the QGraphicsPixmapItem that represents this object.
     *
     * @author Darryl Pogue
     * @author Dean Morin
     * @param qgpi The QGraphicsPixmapItem to be stored.
     */
    void setPixmapItem(QGraphicsPixmapItem* qgpi) {
        mutex_.lock();
        pixmapItem_ = qgpi;
        mutex_.unlock();
    }

signals:
    void created(GraphicsComponent* gc);
    void signalDraw(QPointF pos, GraphicsComponent* gc);
};

#endif

