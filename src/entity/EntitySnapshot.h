#pragma once

#include "EntityType.h"
#include "../math/Vector.h"
#include "../math/BoundingBox.h"

class EntitySnapshot {
public:
    const EntityType *type_;

    const Vector2f position_;

    const AABB boundingBox_;

    bool invulnerable_;

    float health_;

    EntitySnapshot(
            const EntityType *type,
            const Vector2f &position,
            const AABB &boundingBox,
            bool invulnerable,
            float health
    );
};
