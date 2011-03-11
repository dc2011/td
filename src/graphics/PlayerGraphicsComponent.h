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

public:
    /**
     * Instantiates a PlayerGraphicsComponent component
     * @author Warren Voelkl
     */
    PlayerGraphicsComponent();
    //virtual ~PlayerGraphicsComponent();

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
     * The primary method used to determine the behaviours of animation
     *
     * @author Warren Voelkl
     */
    virtual void animate();

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


private:
    /**
     * Slows down how often the images animate from the timer.
     */
    int animateMod;

    /**
     * The number of times the timer has ticked.
     */
    int animateCount;

    /**
     * container for all pixmaps which pertain to the current object
     **/
    static QPixmap * pixmapImgs_;

    /** Text to display the current label_ for this item **/
    QGraphicsTextItem * label_;

    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    virtual QPixmap * getPixmapArray();

};

} /* end namespace td */

#endif

