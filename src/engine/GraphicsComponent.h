#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <QObject>
#include <QPoint>
#include <QGraphicsPixmapItem>

class Player;
class GraphicsComponent : public QObject {
    Q_OBJECT

public:
    GraphicsComponent(QPixmap pixmap) 
    :       pixmapItem_(new QGraphicsPixmapItem(pixmap)) {}
    virtual ~GraphicsComponent() {}
    virtual void update(Player* player) = 0;

    virtual QGraphicsPixmapItem* getPixmapItem() { return pixmapItem_; }

private:
    QGraphicsPixmapItem* pixmapItem_;
};

#endif

