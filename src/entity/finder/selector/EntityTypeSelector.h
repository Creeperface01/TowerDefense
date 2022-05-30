#pragma once

#include "EntitySelector.h"
#include "../../EntityType.h"

#include <vector>
#include <initializer_list>

class EntityTypeSelector : public EntitySelector {
private:
    std::vector<const EntityType *> types_;

public:
    explicit EntityTypeSelector(const EntityType *type);

    EntityTypeSelector(const std::initializer_list<const EntityType *> &types);

    bool select(const Entity *entity) const override;
};
