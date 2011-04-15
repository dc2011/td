#ifndef TD_CONTEXTMENUGRAPHICSCOMPONENTTYPES_H
#define TD_CONTEXTMENUGRAPHICSCOMPONENTTYPES_H

#include "ContextMenuGraphicsComponent.h"

namespace td {

class BuildContextMenuGraphicsComponent : public ContextMenuGraphicsComponent {
    
public:
    BuildContextMenuGraphicsComponent(ContextMenu* menu);

    /**
     * Initializes all of the images for this object.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps();

    /**
     * Changes the index, and sets the position of the context menu to be shown.
     * This function is called when a user chooses a tower he wishes to build
     *
     * @author Karl Castillo, Warren Voelkl
     * @param type - The key pressed. Each keypress is associated with a 
     * specific action.
     * @param playerPos The coordinates of the player, which will be used as a
     * reference as to where the context menu will be painted.
     */
    virtual void showSelectMenu(int type, QPointF playerPos);

protected:
    /**
     * Gets the current image being used for this object.
     *
     * @returns The pixmap array from the current graphics object.
     * @author Warren Voelkl
     */
    virtual QPixmap* getPixmapArray();

    /**
     * Gets the menu image index appropriate for the levels of the upgrades. 
     * (eg. there will be a different image when a tower has been upgraded to 
     * level 3, as opposed to when no upgrades have taken place.
     *
     * @author Dean Morin
     * @return The current base menu image index.
     */
    virtual int getCurrentImage();

private:
    /**
     * container for all pixmaps which pertain to the current object
     **/
    static QPixmap * pixmapImgs_;
};

class TowerContextMenuGraphicsComponent : public ContextMenuGraphicsComponent {
    
public:
    TowerContextMenuGraphicsComponent(ContextMenu* menu);

    /**
     * Initializes all of the images for this object.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps();

    /**
     * Changes the index, and sets the position of the context menu to be shown.
     * This function is called when a user chooses a tower he wishes to build
     *
     * @author Karl Castillo, Warren Voelkl
     * @param type - The key pressed. Each keypress is associated with a 
     * specific action.
     * @param playerPos The coordinates of the player, which will be used as a
     * reference as to where the context menu will be painted.
     */
    virtual void showSelectMenu(int type, QPointF playerPos);

    /**
     * Gets the menu image index appropriate for the levels of the upgrades. 
     * (eg. there will be a different image when a tower has been upgraded to 
     * level 3, as opposed to when no upgrades have taken place.
     *
     * @author Dean Morin
     * @return The current base menu image index.
     */
    virtual int getCurrentImage();

protected:
    /**
     * Gets the current image being used for this object.
     *
     * @returns The pixmap array from the current graphics object.
     * @author Warren Voelkl
     */
    virtual QPixmap* getPixmapArray();

private:
    /**
     * container for all pixmaps which pertain to the current object
     **/
    static QPixmap * pixmapImgs_;
};

class PlayerContextMenuGraphicsComponent : public ContextMenuGraphicsComponent {
    
public:
    PlayerContextMenuGraphicsComponent(ContextMenu* menu);

    /**
     * Initializes all of the images for this object.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps();

    /**
     * Changes the index, and sets the position of the context menu to be shown.
     * This function is called when a user chooses a tower he wishes to build
     *
     * @author Karl Castillo, Warren Voelkl
     * @param type - The key pressed. Each keypress is associated with a 
     * specific action.
     * @param playerPos The coordinates of the player, which will be used as a
     * reference as to where the context menu will be painted.
     */
    virtual void showSelectMenu(int type, QPointF playerPos);

protected:
    /**
     * Gets the current image being used for this object.
     *
     * @returns The pixmap array from the current graphics object.
     * @author Warren Voelkl
     */
    virtual QPixmap* getPixmapArray();

    /**
     * Gets the menu image index appropriate for the levels of the upgrades. 
     * (eg. there will be a different image when a tower has been upgraded to 
     * level 3, as opposed to when no upgrades have taken place.
     *
     * @author Dean Morin
     * @return The current base menu image index.
     */
    virtual int getCurrentImage();

private:
    /**
     * container for all pixmaps which pertain to the current object
     **/
    static QPixmap * pixmapImgs_;
};

} // end namespace td

#endif

