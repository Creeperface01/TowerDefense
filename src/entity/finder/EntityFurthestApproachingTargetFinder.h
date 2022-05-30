#pragma once

#include "EntityTargetFinder.h"

class EntityFurthestApproachingTargetFinder : public EntityTargetFinder {

public:
    EntityFurthestApproachingTargetFinder(
            World *world,
            const std::optional<float> &range = std::nullopt,
            const std::optional<EntitySelector *> &selector = std::nullopt
    );

    std::optional<Entity *> find(Entity *source) override;
};
