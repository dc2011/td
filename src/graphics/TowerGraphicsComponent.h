#ifndef TOWERGRAPHICSCOMPONENT_H
#define TOWERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"
#include "./util/defines.h"
#include <QGraphicsEllipseItem>

namespace td {

class Tower;

class TowerGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates a Tower graphics component
     * @author Warren Voelkl
     */
    TowerGraphicsComponent(): GraphicsComponent() {}
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

    void initRangeCircle(GameObject* obj);

    virtual void draw(DrawParams* dp, int layer=0);

private:
    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    virtual QPixmap * getPixmapArray() = 0;

    QGraphicsEllipseItem * rangeCircle_;
    bool visibleRange_;

public slots:
    void setVisibleRange(bool newValue) {visibleRange_ = newValue;}
};


} /* end namespace td */

#endif

