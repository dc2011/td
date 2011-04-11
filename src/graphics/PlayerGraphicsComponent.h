#ifndef PLAYERGRAPHICSCOMPONENT_H
#define PLAYERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include <QRgb>
#include "GraphicsComponent.h"


namespace td {

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
    QGraphicsPixmapItem* resourcePixmapItem_;

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
    virtual void draw(DrawParams* dp, int layer=0);
    
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
};

} /* end namespace td */

#endif

