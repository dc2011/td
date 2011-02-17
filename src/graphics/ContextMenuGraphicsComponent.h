#ifndef CONTEXTMENUGRAPHICSCOMPONENT_H
#define CONTEXTMENUGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"

class ContextMenuGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    ContextMenuGraphicsComponent();
    virtual ~ContextMenuGraphicsComponent() {}
    
    /**
     * Loads a structure from the item and game component class then sends
     * the structure to the generic draw slot in GraphicsComponent.
     *
     * @author Warren
     **/
    virtual void update(GameObject* obj);
};

#endif

