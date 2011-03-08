#ifndef NPCGRAPHICSCOMPONENT_H
#define NPCGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"

namespace td {

class NPCGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates a NPC graphics component
     * @author Warren Voelkl
     */
    NPCGraphicsComponent();
    virtual ~NPCGraphicsComponent();

    /**
     * Loads a structure from the item and game component class then sends
     * the structure to the generic draw slot in GraphicsComponent.
     *
     * @author Warren Voelkl
     */
    virtual void update(GameObject* obj);

    /**
     * Gets a pixmap for the object based on its current animation state.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps();

protected:

    /**
     * The primary method used to determine the behaviours of animation
     *
     * @author Warren Voelkl, Marcel Vangrootheest
     */
    virtual void animate();
private:

};

} /* end namespace td */

#endif

