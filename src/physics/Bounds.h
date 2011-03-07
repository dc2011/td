#ifndef _BOUNDS_H
#define _BOUNDS_H

#include <QPoint>
#include <QRect>

namespace td {

class Bounds
{
public:
    enum Type {
        kBox,       /**< A Bounding Box. */
        kTriangle,  /**< A Bounding Triangle. */
        kCircle     /**< A Bounding Circle. */
    };

protected:
    /**
     * The type of bounds (box, circle, or triangle).
     */
    Type type_;

    /**
     * Protected Constructor.
     *
     * @param type The type of bounding region.
     */
    Bounds(Type type) : type_(type) { }

public:
    /**
     * Destructor.
     */
    virtual ~Bounds() { }

    /**
     * Gets the type of bounding region.
     *
     * @author Darryl Pogue
     * @return The bounding type.
     */
    Type getType() const {
        return type_;
    }

    /**
     * Returns whether this bounding region intersects the other bounding
     * region.
     *
     * @author Darryl Pogue
     * @param other The bounding region to check for intersections.
     * @return true if there is an intersection, false otherwise.
     */
    virtual bool intersects(const Bounds& other) const = 0;
};

class BoxBounds;
class TriBounds;
class RndBounds;

class BoxBounds : public Bounds
{
protected:
    /**
     * The rectangle that defines the bounding box region.
     */
    QRect box_;

public:
    BoxBounds(QRect box)
            : Bounds(kBox), box_(box) { }
    BoxBounds(QPoint tl, QPoint br)
            : Bounds(kBox), box_(QRect(tl, br)) { }
    BoxBounds(int x, int y, int w, int h)
            : Bounds(kBox), box_(QRect(x, y, w, h)) { }

    /**
     * Destructor.
     */
    ~BoxBounds() { }

    /**
     * Returns whether this bounding region intersects the other bounding
     * region.
     *
     * @author Darryl Pogue
     * @param other The bounding region to check for intersections.
     * @return true if there is an intersection, false otherwise.
     */
    virtual bool intersects(const Bounds& other) const;

    /**
     * Gets the rectangle representation of the bounding box.
     *
     * @author Darryl Pogue
     * @return The bounding box.
     */
    QRect getBox() const {
        return box_;
    }

    /**
     * Sets the bounding box area.
     *
     * @author Darryl Pogue
     * @param box The rectangle to be used as a bounding box.
     */
    void setBox(QRect box) {
        box_ = box;
    }

    /**
     * Gets the centre of the bounding box.
     *
     * @author Darryl Pogue
     * @return The point at the centre of the bounding box.
     */
    QPoint getCentre() const {
        return box_.center();
    }

private:
    /**
     * Returns whether this bounding box intersects the other bounding box.
     *
     * @author Darryl Pogue
     * @param other The bounding box region to check for intersections.
     * @return true if there is an intersection, false otherwise.
     */
    bool intersectBox(const BoxBounds& other) const;
    bool intersectTri(const TriBounds& other) const;
    bool intersectRnd(const RndBounds& other) const;
};

class TriBounds : public Bounds
{
protected:
    /**
     * The "centre" of the triangle. This is actually just the primary
     * vertex, which is used as a pivot point.
     */
    QPoint centre_;

    /**
     * One of the two secondary vertices of the triangle.
     */
    QPoint vert1_;

    /**
     * One of the two secondary vertices of the triangle.
     */
    QPoint vert2_;

public:
    TriBounds(QPoint centre, QPoint v1, QPoint v2)
            : Bounds(kTriangle), centre_(centre), vert1_(v1), vert2_(v2) { }

    /**
     * Destructor.
     */
    ~TriBounds() { }
    
    /**
     * Gets the primary vertex of this bounding triangle.
     *
     * @author Darryl Pogue
     * @return The primary vertex of the bounding triangle.
     */
    QPoint getCentre() const {
        return centre_;
    }

    void setCentre(QPoint& centre) {
        centre_ = centre;
    }

    QPoint getVertex1() const {
        return vert1_;
    }

    QPoint getVertex2() const {
        return vert2_;
    }

    void setVertices(QPoint v1, QPoint v2) {
        vert1_ = v1;
        vert2_ = v2;
    }

    /**
     * Returns whether this bounding region intersects the other bounding
     * region.
     *
     * @author Darryl Pogue
     * @param other The bounding region to check for intersections.
     * @return true if there is an intersection, false otherwise.
     */
    virtual bool intersects(const Bounds& other) const;

private:
    /**
     * Returns whether this bounding triangle intersects the other bounding
     * box.
     *
     * @author Darryl Pogue
     * @param other The bounding box region to check for intersections.
     * @return true if there is an intersection, false otherwise.
     */
    bool intersectBox(const BoxBounds& other) const;
    bool intersectTri(const TriBounds& other) const;
    bool intersectRnd(const RndBounds& other) const;
};

class RndBounds : public Bounds
{
protected:
    QPoint centre_;
    int radius_;

public:
    RndBounds(QPoint centre, int radius)
            : Bounds(kCircle), centre_(centre), radius_(radius) { }

    /**
     * Destructor.
     */
    ~RndBounds() { }

    QPoint getCentre() const {
        return centre_;
    }

    void setCentre(QPoint centre) {
        centre_ = centre;
    }

    int getRadius() const {
        return radius_;
    }

    void setRadius(int radius) {
        radius_ = radius;
    }

    /**
     * Returns whether this bounding region intersects the other bounding
     * region.
     *
     * @author Darryl Pogue
     * @param other The bounding region to check for intersections.
     * @return true if there is an intersection, false otherwise.
     */
    virtual bool intersects(const Bounds& other) const;

private:
    /**
     * Returns whether this bounding circle intersects the other bounding
     * box.
     *
     * @author Darryl Pogue
     * @param other The bounding box region to check for intersections.
     * @return true if there is an intersection, false otherwise.
     */
    bool intersectBox(const BoxBounds& other) const;
    bool intersectTri(const TriBounds& other) const;
    bool intersectRnd(const RndBounds& other) const;
};

} /* end namespace td */

#endif
