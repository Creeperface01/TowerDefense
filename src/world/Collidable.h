#pragma once

#include "../math/BoundingBox.h"

class Collidable {

public:
    [[nodiscard]] virtual const AABB &getBoundingBox() const = 0;

    [[nodiscard]] virtual bool canPassThrough() const = 0;

    [[nodiscard]] bool collidesWith(const Collidable &other) const;
};