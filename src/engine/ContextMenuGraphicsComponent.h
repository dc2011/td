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
    virtual void update(GameObject* obj);
    virtual void draw(QPointF* pos);
};

#endif

