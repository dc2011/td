#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <QMutexLocker>
#include <QObject>
#include <QPoint>
#include <QGraphicsPixmapItem>

#include "GameObject.h"

class GraphicsComponent : public QObject {
    Q_OBJECT

private:
    QGraphicsPixmapItem* pixmapItem_;
    QMutex mutex_;

public:
    GraphicsComponent() { }
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
    void draw(GraphicsComponent* gc);
};

#endif

