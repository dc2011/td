#ifndef PLAYERGRAPHICSCOMPONENT_H
#define PLAYERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"

class ProjectileGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    ProjectileGraphicsComponent();
    virtual ~ProjectileGraphicsComponent();

    /**
     * Loads a structure from the item and game component class then sends
     * the structure to the generic draw slot in GraphicsComponent.
     *
     * @author Warren Voelk
     */
    virtual void update(GameObject* obj);

    /**
     * Gets a pixmap for the object based on its current animation state.
     *
     * @author Warren Voelk
     */
    virtual QPixmap initPixmaps();
};

#endif

