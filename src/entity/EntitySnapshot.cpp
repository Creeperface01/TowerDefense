#include "EntitySnapshot.h"

EntitySnapshot::EntitySnapshot(
        const EntityType *type,
        const Vector2f &position,
        const AABB &boundingBox,
        bool invulnerable,
        float health
) : type_(type),
    position_(position),
    boundingBox_(boundingBox),
    invulnerable_(invulnerable),
    health_(health) {}
