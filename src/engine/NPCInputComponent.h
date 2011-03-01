#ifndef NPCINPUTCOMPONENT_H
#define NPCINPUTCOMPONENT_H

#include <QVector2D>
#include "InputComponent.h"
#include "Unit.h"

class NPC;
class NPCInputComponent : public InputComponent {
    Q_OBJECT
    
public:
    NPCInputComponent();
    virtual ~NPCInputComponent();
    
    void update();
    void setParent(Unit*);

public slots:

private:
    NPC* parent_;
};

#endif // NPCINPUTCOMPONENT_H
