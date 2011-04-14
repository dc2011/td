#ifndef ENDINGGRAPHICSCOMPONENT_H
#define ENDINGGRAPHICSCOMPONENT_H

#include "GraphicsComponent.h"
#include <QDebug>

namespace td {

class EndingGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    EndingGraphicsComponent(const QPointF& pos)
        : GraphicsComponent(), arrayIndexMin_(0), arrayIndexMax_(0),
        currentIndex_(0), timerID_(0),  pos_(pos)  {

    }

    virtual ~EndingGraphicsComponent() {
        this->disconnect();
    }

    virtual void update(GameObject* obj);

    virtual void draw(DrawParams* dp, int layer=0);

    virtual void initPixmaps() = 0;

    virtual void animate();    

protected:
    int arrayIndexMin_;
    int arrayIndexMax_;
    int currentIndex_;
    int timerID_;
    QPointF pos_;

private:
    static QPixmap* pixmapImgs_;

private:
    virtual void setNonStaticValues() = 0;
};

}

#endif
