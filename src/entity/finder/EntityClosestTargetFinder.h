#pragma once

#include "EntityTargetFinder.h"

class EntityClosestTargetFinder : public EntityTargetFinder {
public:

    std::optional<Entity *> find(Entity *source) override;
};
