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
        disconnect(this);
    }

    virtual void update(GameObject* obj);

    virtual void draw(void* dp, int layer=0);

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

    virtual void setLayer(void*) {}
};


// cannon
class CannonEndingGraphicsComponent : public EndingGraphicsComponent {
    Q_OBJECT

public:
    CannonEndingGraphicsComponent(const QPointF& pos)
        : EndingGraphicsComponent(pos) {
        emit created(this);
        timerID_ = this->startTimer(55);
    }

    virtual ~CannonEndingGraphicsComponent() { }

    virtual void initPixmaps();

    virtual QPixmap* getPixmapArray() {
        return pixmapImgs_;
    }

protected:
    void timerEvent(QTimerEvent*) {
        if (currentIndex_++ > arrayIndexMax_ + 1) {
            this->killTimer(timerID_);
            this->deleteComponent();
            return;
        }
        DrawParams* dp = new DrawParams();
        dp->pos = this->pos_;
        this->draw(dp, LAYER_FLYNPC);
    }

private:
    virtual void setNonStaticValues();

private:
    static QPixmap* pixmapImgs_;
};

}

#endif
