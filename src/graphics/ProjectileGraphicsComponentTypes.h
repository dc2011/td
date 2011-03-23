#ifndef TD_PROJECTILEGRAPHICSCOMPONENTTYPES_H
#define TD_PROJECTILEGRAPHICSCOMPONENTTYPES_H

#include "ProjectileGraphicsComponent.h"

namespace td {

class ArrowProjectileGraphicsComponent : public ProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    ArrowProjectileGraphicsComponent() : ProjectileGraphicsComponent() { }

    /**
     * Destructor.
     */
    virtual ~ArrowProjectileGraphicsComponent() { }

    /**
     * Initializes the static array of pixmaps.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps();

    /**
     * Returns the array of pixmap images.
     *
     * @author Warren Voelkl
     * @return The list of static pixmaps used for animations.
     */
    virtual QPixmap* getPixmapArray() {
        return pixmapImgs_;
    }
};

class CannonProjectileGraphicsComponent : public ProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    CannonProjectileGraphicsComponent() : ProjectileGraphicsComponent() { }

    /**
     * Destructor.
     */
    virtual ~CannonProjectileGraphicsComponent() { }

    /**
     * Initializes the static array of pixmaps.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps();

    /**
     * Returns the array of pixmap images.
     *
     * @author Warren Voelkl
     * @return The list of static pixmaps used for animations.
     */
    virtual QPixmap* getPixmapArray() {
        return pixmapImgs_;
    }
};

class TarProjectileGraphicsComponent : public ProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    TarProjectileGraphicsComponent() : ProjectileGraphicsComponent() { }

    /**
     * Destructor.
     */
    virtual ~TarProjectileGraphicsComponent() { }

    /**
     * Initializes the static array of pixmaps.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps();

    /**
     * Returns the array of pixmap images.
     *
     * @author Warren Voelkl
     * @return The list of static pixmaps used for animations.
     */
    virtual QPixmap* getPixmapArray() {
        return pixmapImgs_;
    }
};

class FireProjectileGraphicsComponent : public ProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    FireProjectileGraphicsComponent() : ProjectileGraphicsComponent() { }

    /**
     * Destructor.
     */
    virtual ~FireProjectileGraphicsComponent() { }

    /**
     * Initializes the static array of pixmaps.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps();

    /**
     * Returns the array of pixmap images.
     *
     * @author Warren Voelkl
     * @return The list of static pixmaps used for animations.
     */
    virtual QPixmap* getPixmapArray() {
        return pixmapImgs_;
    }
};

class FlakProjectileGraphicsComponent : public ProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    FlakProjectileGraphicsComponent() : ProjectileGraphicsComponent() { }

    /**
     * Destructor.
     */
    virtual ~FlakProjectileGraphicsComponent() { }

    /**
     * Initializes the static array of pixmaps.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps();

    /**
     * Returns the array of pixmap images.
     *
     * @author Warren Voelkl
     * @return The list of static pixmaps used for animations.
     */
    virtual QPixmap* getPixmapArray() {
        return pixmapImgs_;
    }
};

} /* end namespace td */

#endif

