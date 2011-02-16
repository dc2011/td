#ifndef PROJECTILEGRAPHICSCOMPONENT_H
#define PROJECTILEGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "../engine/GraphicsComponent.h"

class ProjectileGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    ProjectileGraphicsComponent();
    virtual ~ProjectileGraphicsComponent();
    virtual void update(GameObject* obj);
    virtual void draw(QPointF* pos);
};

#endif // PROJECTILEGRAPHICSCOMPONENT_H
