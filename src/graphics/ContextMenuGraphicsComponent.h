#ifndef CONTEXTMENUGRAPHICSCOMPONENT_H
#define CONTEXTMENUGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include <QTimer>
#include "GraphicsComponent.h"

namespace td {

class ContextMenuGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

    struct DrawParamsMenuGraphics {
        /** location */
        QPointF pos;
        /** in degrees 0 is up 180 down... */
        int degrees;
        /** normal is 1 .5 is half 2 is double */
        float scale;
        /** index of pixmap to be displayed */
        int pixmapIdx;
    };

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
     * Gets a pixmap for the object based on its current animation state.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps();

    /**
     * Changes the index, and sets the position of the context menu to be shown.
     *
     * @author Karl Castillo, Warren Voelkl
     * @param playerPos The coordinates of the player, which will be used as a
     * reference as to where the context menu will be paited.
     */
    void showMenu(QPointF playerPos);

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
     * @author Karl Castillo, Warren Voelkl
     * @param type - the keypressed; each keypress (49 - 53) is associated with
     *               a specific type of tower
     * @param playerPos The coordinates of the player, which will be used as a
     * reference as to where the context menu will be paited.
     */
    void showSelectMenu(int type, QPointF playerPos);

    /**
     * Displays the types and amounts of resources required to build each tower.
     *
     * @author Karl Castillo
     * @param show True if the resources should be shown, false if they should
     * be hidden.
     */
    void showResources(bool show);

public slots:
    /**
     * Increments the scale factor for the build context menu every tick of the
     * timer. The timer is stopped when the scale factor reaches a certain amount.
     *
     * @author Karl Castillo, Warren Voelkl
     */
    virtual void animate();

    /**
     * Closes the select menu after a timeout.
     *
     * @author Karl Castillo
     */
    void hideSelectMenu();

private:

    /**
     * Holds the position of the position where the menu is to be painted.
     */
    QPointF menuPos_;

    /**
     * Holds the scale factor that determines the size of the context menu.
     * This variable is for animation purposes only.
     */
    float scaleFactor_;

    /**
     * The timer that is used that will close the select menu after a period
     * of time.
     */
    QTimer closeTimer_;

    /**
     * The next pixmap image that should be displayed by the graphics thread.
     */
    int nextImage_;

    /**
     * container for all pixmaps which pertain to the current object
     **/
    static QPixmap * pixmapImgs_;

    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    virtual QPixmap * getPixmapArray();
};

} /* end namespace td */

#endif
