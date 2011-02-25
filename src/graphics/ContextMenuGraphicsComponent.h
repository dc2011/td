#ifndef CONTEXTMENUGRAPHICSCOMPONENT_H
#define CONTEXTMENUGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"

class ContextMenuGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates the ContextMenuGraphicsComponent
     */
    ContextMenuGraphicsComponent();
    virtual ~ContextMenuGraphicsComponent() {}

    /**
     * Loads a structure from the item and game component class then sends
     * the structure to the generic draw slot in GraphicsComponent.
     *
     * @author Warren, Karl Castillo
     **/
    virtual void update(GameObject* obj);

    /**
     * Gets a pixmap for the object based on its current animation state.
     *
     * @author Warren Voelk
     */
    virtual void initPixmaps();

    /**
     * Changes the index, and sets the position of the context menu to be shown.
     *
     * @author Karl Castillo
     * @param obj - the player object; it will be used as a reference as to where
     *              the context menu will be painted.
     */
    void showMenu(GameObject* obj);

    /**
     * Hides the context menu by relocating the context menu outside the viewing
     * area.
     *
     * @author Karl Castillo
     */
    void hideMenu();

    /**
     * Changes the index, and sets the position of the context menu to be shown.
     * This function is called when a user chooses a tower he wishes to build
     *
     * @author Karl Castillo
     * @param type - the keypressed; each keypress (49 - 53) is associated with
     *               a specific type of tower
     *        obj - the player object; it will be used as a reference as to where
     *              the context menu will be painted.
     */
    void showSelectMenu(int type, GameObject *obj);

private:
    /**
     * Holds the index of the current image that is to be painted.
     */
    int imageIndex;

    /**
     * Holds the position of the position where the menu is to be painted.
     */
    QPointF menuPos;
};

#endif

