#ifndef PLAYERGRAPHICSCOMPONENT_H
#define PLAYERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPoint>
#include "GraphicsComponent.h"

class PlayerGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    PlayerGraphicsComponent(QWidget* gui);
    virtual ~PlayerGraphicsComponent();
    virtual void update(Player* player);
};

#endif

