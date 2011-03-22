#ifndef TOWERGRAPHICSCOMPONENT_H
#define TOWERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"
#include "./util/defines.h"

namespace td {

class Tower;

class TowerGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates a Tower graphics component
     * @author Warren Voelkl
     */
    TowerGraphicsComponent();
    virtual ~TowerGraphicsComponent();

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

private:
    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    virtual QPixmap * getPixmapArray() = 0;

    /**
     * Sets the appropriate index for the selected tower so the correct
     * image is displayed from the pixmaparray
     * @author Warren Voelkl
     */
    void setIndexValue();
};

} /* end namespace td */

#endif

