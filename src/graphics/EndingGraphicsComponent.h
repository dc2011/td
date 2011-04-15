#ifndef ENDINGGRAPHICSCOMPONENT_H
#define ENDINGGRAPHICSCOMPONENT_H

#include <QSemaphore>

#include "GraphicsComponent.h"

namespace td {


class EndingGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
      Constructs the EndingGraphicsComponent based based on the supplied
      position.

      @param pos Location to draw the ending animation.
      @author Nick Huber
      */
    EndingGraphicsComponent(const QPointF& pos)
        : GraphicsComponent(), arrayIndexMin_(0), arrayIndexMax_(0),
        currentIndex_(0), timerID_(0),  pos_(pos), created_(0)  {

    }

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
      */
    virtual void update(GameObject* obj);

    /**
      Draw the object.

      @param dp The daw parameters.
      @param layer Layer to draw the object at.
      @author Nick Huber
      */
    virtual void draw(void* dp, int layer = LAYER_DEFAULT);

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

    /**
      Redraw the animation frame.
      Called from the timer events.

      @param timerLength how long to wait for next animation.
      @param layer Layer to draw on.
      @author Nick Huber
      */
    virtual void redraw(int timerLenght, int layer);

protected:
    int arrayIndexMin_; /**< Minimum index for the array of animations. */
    int arrayIndexMax_; /**< Maximum index for the array of animations. */
    int currentIndex_;  /**< Current index of animation. */
    int timerID_;       /**< Animation timer ID. */
    QPointF pos_;       /**< Position to draw at. */
    QSemaphore created_;/**< Make sure it isn't used till its created. */

private:
    /**
      Setup the non-static variables for each animation.

      @author Nick Huber
      */
    virtual void setNonStaticValues() = 0;

    virtual void setLayer(void*) {}
};

}

#endif
