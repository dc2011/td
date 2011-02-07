#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <QObject>
#include <QPoint>

class Player;
class GraphicsComponent : public QObject {
    Q_OBJECT

public:
    GraphicsComponent(QObject* gui) : gui_(gui) {}
    virtual ~GraphicsComponent() {}
    
protected:
    QObject* gui_; 
    
};

#endif

