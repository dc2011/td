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
     * Sets up the pixmap image, and position of the context menu when space
     * is pressed.
     *
     * @author Karl Castillo
     */
    void showMenu(GameObject* obj);

    /**
     *
     *
     * @author Karl Castillo
     */
    void hideMenu();

    /**
     *
     *
     * @author Karl Castillo
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

