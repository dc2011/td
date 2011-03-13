#ifndef NPCGRAPHICSCOMPONENT_H
#define NPCGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"

#define NPC_PTERO   1
#define NPC_PLEA    2

namespace td {

class NPCGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates a NPC graphics component
     * @author Warren Voelkl
     */
    NPCGraphicsComponent();
    
    NPCGraphicsComponent(int npcType);

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

    virtual void animate();

private:
    /** The current set of images to use for this object */
    int npcType_;

    /** True if the health of the NPC should be displayed. */
    bool showHealth_;

    int arrayIndexMin_;
    int arrayIndexMax_;

    /** Container for all pixmaps which pertain to the current object. */
    static QPixmap * pixmapImgs_;

    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    virtual QPixmap * getPixmapArray();

    /**
     * a switch statement wich will set the animation mod and the min
     * and max values for wich to index into the NPC pixmap array
     */
    void setNonStaticValues();

public slots:
    /**
     * Sets the flag specifying whether or not to show an NPC's health bar.
     * 
     * @author Dean Morin
     * @param keyHeld True if the alt key is currently held down.
     */
    void showHealth(bool keyHeld);
};

} /* end namespace td */

#endif

