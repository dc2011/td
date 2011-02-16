#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QVector2D>
#include <QPointF>

#include "Unit.h"

class Projectile : public Unit {
    Q_OBJECT
public:
    Projectile(PhysicsComponent* physics, Unit* sender, Unit* receiver);

    virtual void update();

    QVector2D& getVelocity();
    void setVelocity(QVector2D&);
    size_t getDamage();
    void setDamage(size_t);
    size_t getDuration();
    void setDuration(size_t);

private:
    QVector2D velocity_;
    size_t damage_;
    size_t duration_;
    Unit* sender_;
    Unit* receiver_;
};

#endif // PROJECTILE_H
