#ifndef PLAYERGRAPHICSCOMPONENT_H
#define PLAYERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"

class PlayerGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    PlayerGraphicsComponent();
    virtual ~PlayerGraphicsComponent();

    /**
     * Loads a structure from the item and game component class then sends
     * the structure to the generic draw slot in GraphicsComponent.
     *
     * @author Warren
     **/
    virtual void update(GameObject* obj);
};

#endif

