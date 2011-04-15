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

struct DrawParamsTower {
    /** location */
    QPointF pos;
    /** in degrees 0 is up 180 down... */
    int degrees;
    /** normal is 1 .5 is half 2 is double */
    float scale;
    /** when true it displays the range of the tower */
    bool displayRadius;
};


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
    /**
     * Sets up the rangeCircle associated with this tower.
     * @param color the color of the range circle for this tower.
     * @author Ian Lee, Warren Voelkl
     */
    void initRangeCircle(QColor color);
    /**
     *
     * @author Ian Lee, Warren Voelkl
     */
    virtual void draw(void* dp, int layer=0);

private:
    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    virtual QPixmap * getPixmapArray() = 0;

    /**
     * range circle object.
     */
    QGraphicsEllipseItem * rangeCircle_;

    bool visibleRange_;
protected:
    int radius_;
public slots:
    /**
     * Slot for alt key pressed to show ranges.
     * @param newValue whether or not key is pressed.
     * @author Ian Lee
     */
    void setVisibleRange(bool newValue) {visibleRange_ = newValue;}
};


} /* end namespace td */

#endif

