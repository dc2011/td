#ifndef PLAYERGRAPHICSCOMPONENT_H
#define PLAYERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPoint>
#include "GraphicsComponent.h"

class PlayerGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    PlayerGraphicsComponent(QObject* gui);
    virtual ~PlayerGraphicsComponent();
    void Update(Player* player);
};

#endif

