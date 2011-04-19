#ifndef PLAYERGRAPHICSCOMPONENT_H
#define PLAYERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include <QRgb>
#include "GraphicsComponent.h"


namespace td {


struct DrawParamsPlayer {
    /** location */
    QPointF pos;
    /** in degrees 0 is up 180 down... */
    int degrees;
    /** normal is 1 .5 is half 2 is double */
    float scale;
    /** true if animate() should be called to set the current image. */
    bool animate;
    /** current moving state of player */
    bool moving;
    /** if the resource bar should currently be shown */
    bool resourceProgressShowing;
    /** the current progress of harvesting a resource */
    double resourceProgress;
    /** The type of resource the player is playing */
    int resourceType;
    /** if the players name should be shown */
    bool showName;
};

class PlayerGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

private:
    /** Container for all pixmaps which pertain to the current object */
    static QPixmap * pixmapImgs_;

    /** Text to display the current label_ for this item **/
    QGraphicsTextItem * label_;

    /** Nickname to be displayed for the player. */
    QString nickname_;
    
    /** True if alt held down and the player's name should be shown. */
    bool showName_;

    /** True if the player's name is currently being shown. */
    bool nameShowing_;

    /** True if the resource progress bar is being shown. */
    bool resourceProgressShowing_;

    /** % amount of resource progress, from 0 to 1. */
    double resourceProgress_;

    /** Graphical progress bar for a resource's progress. */
    QGraphicsRectItem* resourceProgressBar_;

    /** The current resource this object is carrying */
    int resourceType_;

    /** Graphical representation of what the player is carrying. */
    QGraphicsPixmapItem* resourcePixmapItem_;

    /** The player's skin / look. Used as an offset in animate() */
    int outfit_;

public:
    /**
     * Instantiates a PlayerGraphicsComponent component
     * @author Warren Voelkl
     */
    PlayerGraphicsComponent(QString nickname);
    virtual ~PlayerGraphicsComponent() { }

    /**
     * Loads a structure from the item and game component class then sends
     * the structure to the generic draw slot in GraphicsComponent.
     *
     * @author Warren Voelkl
     */
    virtual void update(GameObject* obj);

    /**
     * Resets the matrix then builds the transformation matrix from the
     * structure values.
     *
     * @author Warren Voelkl, Terence Stenvold
     * @param dp Pointer to the drawstruct that contains all the values on how
     * to render an image.
     * @param layer is what layer to draw image defaults to 0
     */
    virtual void draw(void* dp, int layer=0);
    
    /**
     * The primary method used to determine the behaviours of animation
     *
     * @author Warren Voelkl
     */
    virtual void animate();

    /**
     * TODO: Try again, Warren (copy and paste fail)
     * Gets a pixmap for the object based on its current animation state.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps();

    /**
     * Sets whether or not the player's name should be displayed.
     *
     * @author Dean Morin
     * @param showName True if the player's name should be displayed.
     */
    void setShowName(bool showName) {
        showName_ = showName;
    }
    /**
     * Instantiates a PlayerGraphicsComponent component
     * @param resourceType the resource that player is holding or 0 for dropping
     * @author Warren Voelkl
     */
    virtual void setCurrentResource(int resourceType);
    
private:
    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    virtual QPixmap * getPixmapArray() {
        return pixmapImgs_;
    }

    /**
     * Updates the index of the pixmap array.
     * 
     * @author Dean Morin
     * @author index The index to use.
     */
    void setImgIndex(int index);
};

} /* end namespace td */

#endif

