#include <QVector2D>
#include <QPoint>

#include "Unit.h"
#include "Player.h"

class Player : public Unit {
    Q_OBJECT
public:
    Player(QObject *parent = 0);
    ~Player() {};
    
    virtual void Update();
    
    QVector2d& GetVelocity();
    void SetVelocity(QVector2d&);

private:
    QVector2d velocity_;
};