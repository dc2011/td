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
    ArrowProjectileGraphicsComponent();

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

class ArrowProjectileL2GraphicsComponent : public ProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    ArrowProjectileL2GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~ArrowProjectileL2GraphicsComponent() { }

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

class ArrowProjectileL3GraphicsComponent : public ProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    ArrowProjectileL3GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~ArrowProjectileL3GraphicsComponent() { }

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
    CannonProjectileGraphicsComponent();

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

class CannonProjectileL2GraphicsComponent : public ProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    CannonProjectileL2GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~CannonProjectileL2GraphicsComponent() { }

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

class CannonProjectileL3GraphicsComponent : public ProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    CannonProjectileL3GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~CannonProjectileL3GraphicsComponent() { }

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
    TarProjectileGraphicsComponent();

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

class TarProjectileL2GraphicsComponent : public ProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    TarProjectileL2GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~TarProjectileL2GraphicsComponent() { }

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

class TarProjectileL3GraphicsComponent : public ProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    TarProjectileL3GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~TarProjectileL3GraphicsComponent() { }

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

protected:
    int timerID_;
    int arrayIndexMax_;
    int arrayIndexMin_;
    int currentIndex_;

public:
    /**
     * Constructor.
     */
    FireProjectileGraphicsComponent() {}

    /**
     * Destructor.
     */
    virtual ~FireProjectileGraphicsComponent() { }

    /**
     * Initializes the static array of pixmaps.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps() {}

    /**
     * Returns the array of pixmap images.
     *
     * @author Warren Voelkl
     * @return The list of static pixmaps used for animations.
     */
    virtual QPixmap* getPixmapArray() {return NULL;}

    virtual void animate();

protected:
    void timerEvent(QTimerEvent*);
};

class FireProjectileL1GraphicsComponent : public FireProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    FireProjectileL1GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~FireProjectileL1GraphicsComponent() { }

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

class FireProjectileL2GraphicsComponent : public FireProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    FireProjectileL2GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~FireProjectileL2GraphicsComponent() { }

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

class FireProjectileL3GraphicsComponent : public FireProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    FireProjectileL3GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~FireProjectileL3GraphicsComponent() { }

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
    FlakProjectileGraphicsComponent();

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

class FlakProjectileL2GraphicsComponent : public ProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    FlakProjectileL2GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~FlakProjectileL2GraphicsComponent() { }

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

class FlakProjectileL3GraphicsComponent : public ProjectileGraphicsComponent
{
    Q_OBJECT

private:
    /** The array of pixmaps for the animations. */
    static QPixmap* pixmapImgs_;

public:
    /**
     * Constructor.
     */
    FlakProjectileL3GraphicsComponent();

    /**
     * Destructor.
     */
    virtual ~FlakProjectileL3GraphicsComponent() { }

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

