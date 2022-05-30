#pragma once

#include <optional>
#include <vector>

class Entity;

class EntitySelector {

public:
    virtual bool select(const Entity *entity) const = 0;
};
