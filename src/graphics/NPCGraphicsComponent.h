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
     * the structure to the draw function. Also sets the NPC's health
     * before calling the draw function.
     *
     * @author Warren Voelkl, Mohamed Sheriffdeen
     */
    virtual void update(GameObject* obj);

    /**
     * Resets the matrix then builds the transformation matrix from the
     * structure values.
     *
     * @author Warren Voelkl, Terence Stenvold, Mohamed Sheriffdeen
     * @param dp Pointer to the drawstruct that contains all the values on how
     * to render an image.
     * @param layer is what layer to draw image defaults to 0
     */
    virtual void draw(DrawParams* dp, int layer=0);

    /**
     * Gets a pixmap for the object based on its current animation state.
     * Initializes a QGraphicsRectItem to represent the NPC's health as a bar.
     *
     * @author Warren Voelkl, Mohamed Sheriffdeen
     */
    virtual void initPixmaps() = 0;

    virtual void animate();

private:
    /** The current set of images to use for this object */
    int npcType_;

    /** Container for all pixmaps which pertain to the current object. */
    static QPixmap * pixmapImgs_;


    /** The NPC's healthbar. Drawn relative to the NPC's location and it's pixmap. */
    QGraphicsRectItem* healthbarItem_;
    
    /** Percentage of health in decimal form (0 to 1).  */
    double npcHealth;

    /** How many ticks to continue displaying the health bar for, as a result of
     *  the NPC taking damage. */
    int damageDisplayTime_;

    /** True if the key to show all NPCs' health bars is being held. */
    static bool keyHeld_;

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

public slots:
    /**
     * Sets the flag specifying whether or not to show an NPC's health bar,
     * based on the alt key being held down.
     * 
     * @author Dean Morin, Mohamed Sheriffdeen
     * @param keyHeld True if the alt key is currently held down.
     */
    void showHealth(bool keyHeld);

    /**
     * The NPC has just taken damage, and so their health bar must be displayed
     * temporarily.
     *
     * @author Dean Morin
     */
    void showDamage();
};

} /* end namespace td */

#endif

