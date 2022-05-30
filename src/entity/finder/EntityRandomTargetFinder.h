#pragma once

#include "EntityTargetFinder.h"

class EntityRandomTargetFinder : public EntityTargetFinder {

public:
    std::optional<Entity *> find(Entity *source) override;
};
