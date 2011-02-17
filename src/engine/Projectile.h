#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QVector2D>
#include <QPointF>

#include "Unit.h"

class Projectile : public Unit {
    Q_OBJECT
public:
    Projectile(PhysicsComponent* physics, GraphicsComponent* graphics,
               Unit* sender, Unit* receiver);

    virtual void update();

    size_t getDamage(){
        return damage_;
    }

    void setDamage(size_t damage){
        damage_ = damage;
    }

    size_t getDuration(){
        return duration_;
    }

    void setDuration(size_t duration){
        duration_ = duration;
    }

    Unit* getSender() {
        return sender_;
    }

    Unit* getReceiver() {
        return receiver_;
    }

private:
    size_t damage_;
    size_t duration_;
    Unit* sender_;
    Unit* receiver_;
};

#endif // PROJECTILE_H
