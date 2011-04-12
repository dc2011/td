#ifndef TD_COLLECTABLEGRAPHICSCOMPONENTTYPES_H
#define TD_COLLECTABLEGRAPHICSCOMPONENTTYPES_H

#include "CollectableGraphicsComponent.h"

namespace td {

class WoodCollectableGraphicsComponent : public CollectableGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    WoodCollectableGraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~WoodCollectableGraphicsComponent() { }

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

class StoneCollectableGraphicsComponent : public CollectableGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    StoneCollectableGraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~StoneCollectableGraphicsComponent() { }

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

class BoneCollectableGraphicsComponent : public CollectableGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    BoneCollectableGraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~BoneCollectableGraphicsComponent() { }

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

class TarCollectableGraphicsComponent : public CollectableGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    TarCollectableGraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~TarCollectableGraphicsComponent() { }

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

class GemCollectableGraphicsComponent : public CollectableGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    GemCollectableGraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~GemCollectableGraphicsComponent() { }

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


