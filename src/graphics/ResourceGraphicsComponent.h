#ifndef RESOURCEGRAPHICSCOMPONENT_H
#define RESOURCEGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"
#include "./util/defines.h"

namespace td {

class Resource;

class ResourceGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates a Resource graphics component
     * @author Warren Voelkl
     */
    ResourceGraphicsComponent(int resourceType);
    virtual ~ResourceGraphicsComponent();

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

private:

    /** The current type of tower this object currently is */
    int resourceType_;

    /**
     * container for all pixmaps which pertain to the current object
     **/
    static QPixmap * pixmapImgs_;

    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    virtual QPixmap * getPixmapArray();

    /**
     * Sets the appropriate index for the selected tower so the correct
     * image is displayed from the pixmaparray
     * @author Warren Voelkl
     */
    void setIndexValue();

};

} /* end namespace td */

#endif

