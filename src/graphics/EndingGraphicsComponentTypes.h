#ifndef ENDINGGRAPHICSCOMPONENTTYPES_H
#define ENDINGGRAPHICSCOMPONENTTYPES_H

#include "EndingGraphicsComponent.h"

namespace td {

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
    void timerEvent(QTimerEvent*);

private:
    virtual void setNonStaticValues();

private:
    static QPixmap* pixmapImgs_;
};

}

#endif
