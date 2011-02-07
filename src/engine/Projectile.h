#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QVector2D>
#include <QPoint>

#include "Unit.h"

class Projectile : public Unit {
    Q_OBJECT
public:
    Projectile(PhysicsComponent* physics, Unit* sender, Unit* receiver);

    virtual void Update();

    QVector2D& GetVelocity();
    void SetVelocity(QVector2D&);
    size_t GetDamage();
    void SetDamage(size_t);
    size_t GetDuration();
    void SetDuration(size_t);

private:
    QVector2D velocity_;
    size_t damage_;
    size_t duration_;
    Unit* sender_;
    Unit* receiver_;
};

#endif // PROJECTILE_H
