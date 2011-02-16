#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPointF>

#include "PhysicsComponent.h"


class GameObject : public QObject {
  Q_OBJECT
public:
    virtual ~GameObject() {};
    
    /**
     * Returns object's position co-ords.
     * 
     * @author Tom Nightingale
     * @return QPointF.
     */
    QPointF& getPos() {
        return pos_;
    }
    
    /**
     * Sets object's position co-ords.
     * 
     * @author Tom Nightingale
     */
    void setPos(QPointF& p) {
        pos_.setX(p.x());
        pos_.setY(p.y());
        qDebug("Pos: (%.2f, %.2f)", (float) pos_.x(), (float) pos_.y());
    }

public slots:
    
    /**
     * Pure virtual method that all inheriting classes need to implement.
     * This method is the starting point for responses to all events that affect the object.
     * It is a slot and thus is called when a signal is bound to it.
     * 
     * @author Tom Nightingale
     */
    virtual void update() = 0;

protected:
    QPointF pos_;
};
#endif
