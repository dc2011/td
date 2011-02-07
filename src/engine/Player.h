#ifndef PLAYER_H
#define PLAYER_H

#include <QVector2D>
#include <QPoint>

#include "Unit.h"

class Player : public Unit {
    Q_OBJECT
public:
    Player(InputComponent* input, PhysicsComponent* physics, 
           GraphicsComponent* graphics);
    
    virtual void Update();
    
    QVector2D& GetVelocity();
    void SetVelocity(QVector2D&);

private:
    QVector2D velocity_;
};

#endif
