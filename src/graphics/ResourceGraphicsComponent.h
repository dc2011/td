#ifndef RESOURCEGRAPHICSCOMPONENT_H
#define RESOURCEGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"

namespace td {

class Resource;

class ResourceGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates a Resource graphics component
     * @author Warren Voelkl
     */
    ResourceGraphicsComponent(QString pixmapPath);
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
    /** 
     * TODO: remove, hack to get multiple towers working until Warren figures
     * out the static image issue. 
     */
    QString pixmapPath_;

    static QPixmap * pixmapImgs_;

    /**
     * @returns the pixmap array from the subclasses
     */
    virtual QPixmap * getPixmapArray();
};

} /* end namespace td */

#endif

