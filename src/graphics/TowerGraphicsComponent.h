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
    /** true if animate() should be called to set the current image. */
    bool animate;
    /** when true it displays the range of the tower */
    bool displayRadius;
    /** index of pixmap to be displayed */
    int pixmapIdx;
    /** The level of the tower that owns this component. */
    int towerLevel;
};


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
    virtual void initPixmaps();

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

    /**
     * Sets whether or not the tower is firing a projectile.
     *
     * @author Dean Morin
     * @param firing True if firing animation should be shown.
     */
    void setFiring(bool firing) {
        firing_ = firing;
    }

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
    
    /** Tower level indicator triangle for levels 2 and 4. */
    QGraphicsPixmapItem* levelIndicator_;
        
    /** True if the level indicator is currently being displayed. */
    bool levelIndicatorShowing_;

protected:
    int radius_;

    /** True if the tower just fired and needs to animate accordingly. */
    bool firing_;

    /** True if the animation timer is currently running. */
    bool timerRunning_;

    /** Animation timer id. */
    int timerID_;

    /** The time in milleseconds that the firing animation lingers for. */
    int reloadTime_; 

    /** True if the tower type has a firing animation. */
    bool hasFiringAnimation_;

    /**
     * Timer event that indicates to change back from the firing sprite.
     *
     * @author Dean Morin
     */
    void timerEvent(QTimerEvent*);

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

