#ifndef _TOWERGRAPHICSCOMPONENTTYPES_H
#define _TOWERGRAPHICSCOMPONENTTYPES_H

#include "TowerGraphicsComponent.h"

namespace td {

class ArrowTowerGraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    ArrowTowerGraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~ArrowTowerGraphicsComponent() { }

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

class CannonTowerGraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    CannonTowerGraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~CannonTowerGraphicsComponent() { }

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

class TarTowerGraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    TarTowerGraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~TarTowerGraphicsComponent() { }

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

class FlameTowerGraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    FlameTowerGraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~FlameTowerGraphicsComponent() { }

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

class FlakTowerGraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    FlakTowerGraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~FlakTowerGraphicsComponent() { }

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
