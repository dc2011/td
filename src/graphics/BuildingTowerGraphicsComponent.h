#ifndef BUILDINGTOWERGRAPHICSCOMPONENT_H
#define BUILDINGTOWERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"
#include "./util/defines.h"

namespace td {

class BuildingTowerGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates a Tower graphics component
     * @author Warren Voelkl
     */
    BuildingTowerGraphicsComponent();
    virtual ~BuildingTowerGraphicsComponent();

    /**
     * Loads a structure from the item and game component class then sends
     * the structure to the generic draw slot in GraphicsComponent.
     *
     * @author Warren Voelkl
     */
    void update(GameObject* obj);

    /**
     * Gets a pixmap for the object based on its current animation state.
     *
     * @author Warren Voelkl
     */
    void initPixmaps();

private:
    /**
     * container for all pixmaps which pertain to the current object
     **/
    static QPixmap * pixmapImgs_;

    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    QPixmap * getPixmapArray() {
        return pixmapImgs_;
    }
};

} /* end namespace td */

#endif

