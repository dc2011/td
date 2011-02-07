#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <QObject>
#include <QPoint>
#include <QGraphicsPixmapItem>

class Player;
class GraphicsComponent : public QGraphicsPixmapItem {

public:
    GraphicsComponent(QPixmap pm) : QGraphicsPixmapItem(pm) {}
    virtual ~GraphicsComponent() {}
    virtual void updatePosition(Player* player) = 0;
};

#endif

