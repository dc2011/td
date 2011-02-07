#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPoint>

#include "PhysicsComponent.h"


class GameObject : public QObject {
  Q_OBJECT
public:
    virtual ~GameObject() {};
    
    /**
     * Returns object's position co-ords.
     * 
     * @author Tom Nightingale
     * @return QPoint.
     */
    QPoint& getPos() {
        return pos_;
    }
    
    /**
     * Sets object's position co-ords.
     * 
     * @author Tom Nightingale
     */
    void setPos(QPoint& p) {
        pos_.setX(p.x());
        pos_.setY(p.y());
        qDebug("Pos: (%d, %d)", (int) pos_.x(), (int) pos_.y());
    }

public slots:
    virtual void update() = 0;

private:
    QPoint pos_;
};
#endif
