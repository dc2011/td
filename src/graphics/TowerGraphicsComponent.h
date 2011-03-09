#ifndef TOWERGRAPHICSCOMPONENT_H
#define TOWERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"

namespace td {

class Tower;

class TowerGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates a Tower graphics component
     * @author Warren Voelkl
     */
    TowerGraphicsComponent(QString pixmapPath);
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
    virtual void initPixmaps();

private:
    /** 
     * TODO: remove, hack to get multiple towers working until Warren figures
     * out the static image issue. 
     */
    QString pixmapPath_;
};

} /* end namespace td */

#endif

