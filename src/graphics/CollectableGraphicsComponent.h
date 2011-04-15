#ifndef TD_COLLECTABLEGRAPHICSCOMPONENT_H
#define TD_COLLECTABLEGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"

namespace td {

class CollectableGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates a collectable graphics component
     * @author Warren Voelkl
     */
    CollectableGraphicsComponent(): GraphicsComponent(), flickerShow_(false) {}
    virtual ~CollectableGraphicsComponent();

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
    virtual void initPixmaps() = 0;

    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    virtual QPixmap * getPixmapArray() = 0;

private:
    /** Determines whether to show the collectable while it's flickering. */
    bool flickerShow_;
};

} /* end namespace td */

#endif

