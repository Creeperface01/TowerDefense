#pragma once

#include "EntitySelector.h"

#include <functional>

class Entity;

class EntityPredicateSelector : public EntitySelector {
private:
    std::function<bool(const Entity *)> predicate;

public:
    explicit EntityPredicateSelector(std::function<bool(const Entity *)> predicate);

    bool select(const Entity *entity) const override;
};
