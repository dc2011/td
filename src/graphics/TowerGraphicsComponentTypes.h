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

class ArrowTowerL2GraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    ArrowTowerL2GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~ArrowTowerL2GraphicsComponent() { }

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

class ArrowTowerL3GraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    ArrowTowerL3GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~ArrowTowerL3GraphicsComponent() { }

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

class CannonTowerL2GraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    CannonTowerL2GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~CannonTowerL2GraphicsComponent() { }

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

class CannonTowerL3GraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    CannonTowerL3GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~CannonTowerL3GraphicsComponent() { }

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

class TarTowerL2GraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    TarTowerL2GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~TarTowerL2GraphicsComponent() { }

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

class TarTowerL3GraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    TarTowerL3GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~TarTowerL3GraphicsComponent() { }

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

class FlameTowerL2GraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    FlameTowerL2GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~FlameTowerL2GraphicsComponent() { }

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

class FlameTowerL3GraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    FlameTowerL3GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~FlameTowerL3GraphicsComponent() { }

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

class FlakTowerL2GraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    FlakTowerL2GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~FlakTowerL2GraphicsComponent() { }

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

class FlakTowerL3GraphicsComponent : public TowerGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    FlakTowerL3GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~FlakTowerL3GraphicsComponent() { }

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
