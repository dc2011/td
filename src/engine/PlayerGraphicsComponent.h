#ifndef PLAYERGRAPHICSCOMPONENT_H
#define PLAYERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPoint>
#include "GraphicsComponent.h"

class PlayerGraphicsComponent : public GraphicsComponent {

public:
    PlayerGraphicsComponent(const char* pixmap);
    virtual ~PlayerGraphicsComponent();
    virtual void updatePosition(Player* player);
};

#endif

