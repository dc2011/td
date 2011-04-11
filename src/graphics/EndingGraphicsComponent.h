#ifndef ENDINGGRAPHICSCOMPONENT_H
#define ENDINGGRAPHICSCOMPONENT_H

#include "GraphicsComponent.h"

namespace td {

class EndingGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    EndingGraphicsComponent();

    virtual ~EndingGraphicsComponent();

    virtual void update(GameObject* obj);

    virtual void draw(DrawParams* dp, int layer=0);

    virtual void initPixmaps() = 0;

    virtual void animate();
};

class CannonEndingGraphicsComponent : public EndingGraphicsComponent {
    Q_OBJECT

public:
    CannonEndingGraphicsComponent();

    virtual ~CannonEndingGraphicsComponent();

private:
    static QPixmap* pixmapImgs_;
};

}

#endif
