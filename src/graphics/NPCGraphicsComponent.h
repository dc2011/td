#ifndef NPCGRAPHICSCOMPONENT_H
#define NPCGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include <QGraphicsRectItem>
#include <QRectF>
#include "GraphicsComponent.h"

#define NPC_PTERO   1
#define NPC_PLEA    2

namespace td {

class NPCGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates a NPC graphics component
     * @author Warren Voelkl
     */
    NPCGraphicsComponent();
    
    //NPCGraphicsComponent(int npcType);

    virtual ~NPCGraphicsComponent();

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
     * Gets a pixmap for the object based on its current animation state.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps() = 0;

    virtual void animate();

    /**
     * Sets whether or not the NPC's health should be displayed.
     *
     * @author Dean Morin
     * @param showName True if the NPC's health should be displayed.
     */
    void setShowHealth(bool showHealth) {
        showHealth_ = showHealth;
    }

private:
    /** The current set of images to use for this object */
    int npcType_;

    /** Container for all pixmaps which pertain to the current object. */
    static QPixmap * pixmapImgs_;

    /**  */
    QGraphicsRectItem* healthbarItem_;
    
    /** Percentage of health in decimal form (0 to 1).  */
    double npcHealth;


    /** True if the health of the NPC should be displayed. */
    static bool showHealth_;

    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    virtual QPixmap * getPixmapArray() = 0;

    /**
     * a switch statement wich will set the animation mod and the min
     * and max values for wich to index into the NPC pixmap array
     */
    virtual void setNonStaticValues() = 0;
    
    virtual void setLayer(DrawParams* dp) = 0;

protected:

    int arrayIndexMin_;
    int arrayIndexMax_;
    
    void initHealthbar();
};

} /* end namespace td */

#endif

