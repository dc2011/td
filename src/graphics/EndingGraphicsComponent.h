#ifndef ENDINGGRAPHICSCOMPONENT_H
#define ENDINGGRAPHICSCOMPONENT_H

#include "GraphicsComponent.h"
#include <QDebug>

namespace td {

class EndingGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    EndingGraphicsComponent(const QPointF& pos)
        : GraphicsComponent(), pos_(pos), currentIndex_(0)  {

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
    int currentIndex_;
    int timerID_;
    QPointF pos_;

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
    CannonEndingGraphicsComponent(const QPointF& pos)
        : EndingGraphicsComponent(pos) {
        emit created(this);
        timerID_ = this->startTimer(35);
    }

    virtual ~CannonEndingGraphicsComponent() { }

    virtual void initPixmaps();

    virtual QPixmap* getPixmapArray() {
        return pixmapImgs_;
    }

protected:
    void timerEvent(QTimerEvent*) {
        if (currentIndex_++ > arrayIndexMax_ + 1) {
            this->deleteComponent();
            this->killTimer(timerID_);
            return;
        }
        DrawParams* dp = new DrawParams();
        dp->pos = this->pos_;
        this->draw(dp, LAYER_FLYNPC);
    }

private:
    virtual void setLayer(DrawParams *dp);

    virtual void setNonStaticValues();

private:
    static QPixmap* pixmapImgs_;
};

}

#endif
