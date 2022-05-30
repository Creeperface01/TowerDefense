#include "Vector.h"

#include "Direction.h"

size_t std::hash<Vector2i>::operator()(const Vector2i &x) const {
    return x.index2d();
}