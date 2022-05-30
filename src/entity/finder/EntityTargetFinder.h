#pragma once

#include "../EntityType.h"
#include "selector/EntitySelector.h"

#include <optional>
#include <memory>

class World;

class Entity;

class EntityTargetFinder {

protected:
    World *world_;

    std::unique_ptr<EntitySelector> selector_;

    std::optional<float> range_;

public:
    EntityTargetFinder(World *world, std::optional<float> range, std::optional<EntitySelector *> selector);

    virtual std::optional<Entity *> find(Entity *source) = 0;

    bool matches(const Entity *source, const Entity *entity) const;
};
