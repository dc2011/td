#include "Bounds.h"

namespace td {

bool TriBounds::intersects(const Bounds& other) const {
    switch (other.getType()) {
        case kBox:
            return intersectBox((const BoxBounds&)other);
        case kTriangle:
            return intersectTri((const TriBounds&)other);
        case kCircle:
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

} /* end namespace td */
