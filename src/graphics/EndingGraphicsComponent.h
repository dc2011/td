#ifndef ENDINGGRAPHICSCOMPONENT_H
#define ENDINGGRAPHICSCOMPONENT_H

#include "GraphicsComponent.h"

namespace td {

class EndingGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    EndingGraphicsComponent() : GraphicsComponent() {

    }

    virtual ~EndingGraphicsComponent() {
        disconnect(this);
    }

    virtual void update(GameObject* obj);

    virtual void draw(DrawParams* dp, int layer=0);

    virtual void initPixmaps() = 0;

    virtual void animate();

protected:
    int arrayIndexMin_;
    int arrayIndexMax_;

private:
    virtual void setNonStaticValues() = 0;

    virtual void setLayer(DrawParams* dp) = 0;

private:
    static QPixmap* pixmapImgs_;
};


// cannon
class CannonEndingGraphicsComponent : public EndingGraphicsComponent {
    Q_OBJECT

public:
    CannonEndingGraphicsComponent() : EndingGraphicsComponent() {
        emit created(this);
    }

    virtual ~CannonEndingGraphicsComponent() { }

    virtual void initPixmaps();

private:
    virtual void setLayer(DrawParams *dp);

    virtual void setNonStaticValues();

private:
    static QPixmap* pixmapImgs_;
};

}

#endif
