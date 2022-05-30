#include "world/Collidable.h"

bool Collidable::collidesWith(const Collidable &other) const {
    return this->getBoundingBox().intersectsWith(other.getBoundingBox());
}
