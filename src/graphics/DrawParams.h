#ifndef DRAWPARAMS_H
#define DRAWPARAMS_H

/**
 * Contains all the parameters needed to render a graphical object. The 
 * physics logic updates the logical object's position, scale, etc., and 
 * then copies of those values are stored in this struct. A pointer to this
 * struct will then be passed to the rendering thread via a signal, where
 * its values will be read to display the object.
 *
 * Since the struct is dynamically allocated, it is vital that delete is
 * called on it once it has been used.
 * 
 * @author Warren Voekl
 * @author Dean Morin
 */
struct DrawParams {
    /** location */
    QPointF pos;
    /** in degrees 0 is up 180 down... */
    int degrees;
    /** normal is 1 .5 is half 2 is double */
    float scale;
    /** movement for animation projectiles get bigger/smaller during arc */
    bool moving;
};

Q_DECLARE_METATYPE(DrawParams);

#endif

