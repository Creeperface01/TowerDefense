#include "EntityFurthestApproachingTargetFinder.h"

#include "../../world/World.h"

#include <numbers>
#include <iostream>

EntityFurthestApproachingTargetFinder::EntityFurthestApproachingTargetFinder(
        World *world,
        const std::optional<float> &range,
        const std::optional<EntitySelector *> &selector
)
        : EntityTargetFinder(world, range, selector) {}

bool isApproaching(const Vector2f &point, const Entity *e) {
    Vector2f vec = point - e->getPosition();

    float angle = vec.angleBetween(e->getMotion());

    return angle < (std::numbers::pi_v<float> / 2.0f);
}

std::optional<Entity *> EntityFurthestApproachingTargetFinder::find(Entity *source) {
    float distance = std::numeric_limits<float>::max();
    std::optional<Entity *> target;

    for (const auto &item: world_->getEntities()) {
        if (!matches(source, item.second.get())) {
            continue;
        }

        if (!isApproaching(source->getPosition(), item.second.get())) {
            continue;
        }

        float d = source->getPosition().distanceSquared(item.second->getPosition());

        if (d > distance) {
            continue;
        }

        distance = d;
        target = item.second.get();
    }

    return target;
}
