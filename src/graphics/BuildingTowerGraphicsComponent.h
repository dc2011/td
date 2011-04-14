#ifndef BUILDINGTOWERGRAPHICSCOMPONENT_H
#define BUILDINGTOWERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"
#include "./util/defines.h"

#define ICON_MAX 3

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

    /**
     * @param resourceType the definded value of the current resource being set
     * @param num the new value for the resources required
     * @author Warren Voelkl
     */
    void setBuildingResources(int resourceType, int num);

    /**
     * Sets the currently dispalyed graphics item for the current stage
     * @param i the current building stage
     * @author Warren Voelkl
     */
    void setBuildingStage(int i);
    /**
     * Draw functions that displays icons on top of tower when r is pressed
     * @author Warren Voelkl
     */
    virtual void draw(DrawParams* dp, int layer=0);

public slots:
    /**
     * Slot connected to the k keypress used to display the icons required
     * to finish construction of tower
     */
    //void showIcons(bool);

private:
    /** container for all pixmaps which pertain to the current object */
    static QPixmap * pixmapImgs_;
    /** arragy of pix map items for the required resources **/
    QGraphicsPixmapItem *
        resourcePixmapItemArray_[RESOURCE_TYPE_MAX][ICON_MAX];
    /** Number of wood icons to display on tile */
    int woodReq_;
    /** Number of bone icons to display on tile */
    int boneReq_;
    /** Number of stone icons to display on tile */
    int stoneReq_;
    /** Number of tar icons to display on tile */
    int tarReq_;
    /** True if the key to show all NPCs' health bars is being held. */
    static bool keyHeld_;
    /** The current building stage of the graphics component */
    int buildingStage_;



    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    QPixmap * getPixmapArray() {
        return pixmapImgs_;
    }

    /**
     * Sets the default images and visibilities for all the tower icons.
     * @author Warren Voelkl
     */
    void setIconImages();

    /**
     * Sets or unsets visibility of icon.
     *
     * @param iconGraphic current graphics item being evaluated
     * @param index current index to be shown
     * @param current number of resources required for tower completing
     * @author Warren Voelkl
     */
    void setIconVisibility(QGraphicsPixmapItem *iconGraphic, int index,
            int resourceReq);
    /**
     * Sets the position and scale for each icon
     * @param icon the current icon being set
     * @param x the x position of parent
     * @param y the y position of parent
     * @param layer draw icons above tower
     * @param i used to determine y offset of each icon
     * @author Warren Voelkl
     */
    void iconDrawingHelper(QGraphicsPixmapItem *icon, int x, int y,
            int layer, int i);
    /**
     * Updates the current graphic to represent the current building stage
     * @param gpi the graphics pixmap item for wich the image is being set
     * @author Warren Voelkl
     */
    void setBuildingGraphic(QGraphicsPixmapItem * gpi);


};

} /* end namespace td */

#endif

