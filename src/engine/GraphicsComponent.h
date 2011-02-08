#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <QMutexLocker>
#include <QObject>
#include <QPoint>
#include <QGraphicsPixmapItem>

class Player;
class GraphicsComponent : public QObject {
    Q_OBJECT

public:
    GraphicsComponent(const char* pixmap) {
        // send signal to rendering thread here? (pixmap is the path to an image)    
    }
    virtual ~GraphicsComponent() {}
    virtual void update(Player* player) = 0;

    virtual QGraphicsPixmapItem* getPixmapItem() { 
        return pixmapItem_;
    }


private:
    QGraphicsPixmapItem* pixmapItem_;
};

#endif

