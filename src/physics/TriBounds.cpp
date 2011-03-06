#include "Bounds.h"
#include <cmath>

namespace td {

bool TriBounds::intersects(const Bounds& other) const {
    switch (other.getType()) {
        case kBox:
            return intersectBox((const BoxBounds&)other);
        case kTriangle:
            return intersectTri((const TriBounds&)other);
        case kCircle:
            return intersectRnd((const RndBounds&)other);
        default:
            return false;
    }
}

bool TriBounds::intersectBox(const BoxBounds& other) const {
    return false;
}

bool TriBounds::intersectTri(const TriBounds& other) const {
    return false;
}

bool TriBounds::intersectRnd(const RndBounds& other) const {
    int r2 = other.getRadius()^2;

    /* TODO: Check if the centre of the circle is inside the triangle */

    for (int i = 0; i < 3; i++) {
        QPoint P;
        QPoint D;

        if (i == 0) {
            P = getCentre();
            D = getVertex1();
        } else if (i == 1) {
            P = getCentre();
            D = getVertex2();
        } else if (i == 2) {
            P = getVertex1();
            D = getVertex2();
        }

        QPoint l = other.getCentre() - P;
        int s = l.x() * D.x() + l.y() * D.y(); /* Dot product */
        int l2 = l.x() * l.x() + l.y() * l.y(); /* Length squared */

        if (s < 0 && l2 > r2) {
            continue;
        }
        int m2 = l2 - (s * s);
        if (m2 > r2) {
            continue;
        }

        int q = (int)sqrt(r2 - m2);
        int t = -1;
        if ( l2 > r2) {
            t = s - q;
        }
        if (t >= 1 || t < 0) {
            t = s + q;

            if (t >= 1 || t < 0) {
                continue;
            }
        }
        return true;
    }

    return false;
}

} /* end namespace td */
