#ifndef ENDINGGRAPHICSCOMPONENT_H
#define ENDINGGRAPHICSCOMPONENT_H

#include "GraphicsComponent.h"
#include <QSemaphore>

namespace td {


class EndingGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Constructs the EndingGraphicsComponent based based on the supplied
     * position.
     *
     * @author Nick Huber
     * @author Dean Morin
     * @param pos Location to draw the ending animation.
     * @param layer The z-layer to draw the object at.
     * @param timerLength How many milliseconds to wait for the next animation.
     */
    EndingGraphicsComponent(const QPointF& pos, const int layer, 
                            const int timerLength);

    /**
      Destroy the component, disconnect all signals.
      @author Nick Huber
      */
    virtual ~EndingGraphicsComponent() {
        this->disconnect();
    }

    /**
      Update the objects location.

      @param obj Game object to update.
      @author Nick Huber
      @author Dean Morin
      */
    virtual void update(GameObject* obj);

    /**
      Initilize the pixmaps for each object,
      @author Nick Huber
      */
    virtual void initPixmaps() = 0;

    /**
      Run the animation.

      @author Nick Huber
      */
    virtual void animate();

protected:
    int arrayIndexMin_; /**< Minimum index for the array of animations. */
    int arrayIndexMax_; /**< Maximum index for the array of animations. */
    int currentIndex_;  /**< Current index of animation. */
    int timerID_;       /**< Animation timer ID. */
    QPointF pos_;       /**< Position to draw at. */
    QSemaphore created_;/**< Make sure it isn't used till its created. */
    int layer_;         /**< Z-layer of the object. */
    int timerLength_;   /**< Time between animation states. */

    /**
     * Sets the z-layer for this object to be drawn at.
     *
     * @author Dean Morin
     * @param layer The layer to draw the object at.
     */
    void setLayer(int layer) {
        layer_ = layer; 
    }

    /**
     * Sets the time in milleseconds between each state of animation.
     *
     * @author Dean Morin
     * @param length Time between animation states.
     */
    void setTimerLength(int length) {
        timerLength_ = length;
    }

private:
    /**
      Setup the non-static variables for each animation.

      @author Nick Huber
      */
    virtual void setNonStaticValues() = 0;
};

}

#endif
