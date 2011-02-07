#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <QObject>
#include <QPoint>
#include <QWidget>

class Player;
class GraphicsComponent : public QObject {
    Q_OBJECT

public:
    GraphicsComponent(QWidget* gui) : gui_(gui) {}
    virtual ~GraphicsComponent() {}
    virtual void update(Player* player) = 0;
    
protected:
    QWidget* gui_; 
};

#endif

