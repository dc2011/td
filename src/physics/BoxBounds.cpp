#include "Bounds.h"
#include <QLineF>
#include <cmath>
#include <cstdlib>

namespace td {

bool BoxBounds::intersects(const Bounds& other) const {
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

bool BoxBounds::intersectBox(const BoxBounds& other) const {
    return box_.intersects(other.box_);
}

bool BoxBounds::intersectTri(const TriBounds& other) const {
    /* This function borrowed faithfully from a wonderfl (:3) discussion on
     * calculating triangle collision with AABBs on the following blog:
     * http://sebleedelisle.com/2009/05/super-fast-trianglerectangle-intersection-test/
     *
     * This particular optimization was contributed to the discussion by 
     * someone from http://lab9.fr/
     *
     * Translated from JavaScript by Darryl Pogue
     * JS Source: http://pastebin.com/XhgvBzVw
     */
    int l = box_.x();
    int r = box_.x() + box_.width();
    int t = box_.y();
    int b = box_.y() + box_.height();

    int x0 = other.getCentre().x();
    int y0 = other.getCentre().y();
    int x1 = other.getVertex1().x();
    int y1 = other.getVertex1().y();
    int x2 = other.getVertex2().x();
    int y2 = other.getVertex2().y();

    int b0 = ((x0 > l) ? 1 : 0) | (((y0 > t) ? 1 : 0) << 1) |
             (((x0 > r) ? 1 : 0) << 2) | (((y0 > b) ? 1 : 0) << 3);
    if (b0 == 3) {
        return true;
    }

    int b1 = ((x1 > l) ? 1 : 0) | (((y1 > t) ? 1 : 0) << 1) |
             (((x1 > r) ? 1 : 0) << 2) | (((y1 > b) ? 1 : 0) << 3);
    if (b1 == 3) {
        return true;
    }

    int b2 = ((x2 > l) ? 1 : 0) | (((y2 > t) ? 1 : 0) << 1) |
             (((x2 > r) ? 1 : 0) << 2) | (((y2 > b) ? 1 : 0) << 3);
    if (b2 == 3) {
        return true;
    }

    int c = 0;
    int m = 0;
    int s = 0;
    int i = b0 ^ b1;

    if (i != 0) {
        m = (y1 - y0) / (x1 - x0);
        c = y0 - (m * x0);
        if (i & 1) {
            s = m * l + c;
            if (s > t && s < b) {
                return true;
            }
        }
        if (i & 2) {
            s = (t - c) / m;
            if (s > l && s < r) {
                return true;
            }
        }
        if (i & 4) {
            s = m * r + c;
            if (s > t && s < b) {
                return true;
            }
        }
        if (i & 8) {
            s = (b - c) / m;
            if (s > l && s < r) {
                return true;
            }
        }
    }

    i = b1 ^ b2;
    if (i != 0) {
        m = (y2 - y1) / (x2 - x1);
        c = y1 - (m * x1);
        if (i & 1) {
            s = m * l + c;
            if (s > t && s < b) {
                return true;
            }
        }
        if (i & 2) {
            s = (t - c) / m;
            if (s > l && s < r) {
                return true;
            }
        }
        if (i & 4) {
            s = m * r + c;
            if (s > t && s < b) {
                return true;
            }
        }
        if (i & 8) {
            s = (b - c) / m;
            if (s > l && s < r) {
                return true;
            }
        }
    }

    i = b0 ^ b2;
    if (i != 0) {
        m = (y2 - y0) / (x2 - x0);
        c = y0 - (m * x0);
        if (i & 1) {
            s = m * l + c;
            if (s > t && s < b) {
                return true;
            }
        }
        if (i & 2) {
            s = (t - c) / m;
            if (s > l && s < r) {
                return true;
            }
        }
        if (i & 4) {
            s = m * r + c;
            if (s > t && s < b) {
                return true;
            }
        }
        if (i & 8) {
            s = (b - c) / m;
            if (s > l && s < r) {
                return true;
            }
        }
    }
    return false;
}

bool BoxBounds::intersectRnd(const RndBounds& other) const {
    int rad = other.getRadius();

    int r = box_.x() + box_.width();
    int b = box_.y() + box_.height();

    QRect h(box_.x() - rad, box_.y(), r + rad, b);
    if (h.contains(other.getCentre(), true)) {
        return true;
    }

    QRect v(box_.x(), box_.y() - rad, r, b + rad);
    if (v.contains(other.getCentre(), true)) {
        return true;
    }

    QLineF ln(box_.topLeft(), other.getCentre());
    if (abs((int)ln.length()) <= other.getRadius()) {
        return true;
    }

    ln.setPoints(box_.topRight(), other.getCentre());
    if (abs((int)ln.length()) <= other.getRadius()) {
        return true;
    }

    ln.setPoints(box_.bottomLeft(), other.getCentre());
    if (abs((int)ln.length()) <= other.getRadius()) {
        return true;
    }

    ln.setPoints(box_.bottomRight(), other.getCentre());
    if (abs((int)ln.length()) <= other.getRadius()) {
        return true;
    }

    return false;
}

} /* end namespace td */
