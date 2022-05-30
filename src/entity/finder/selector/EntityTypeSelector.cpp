#include "EntityTypeSelector.h"

#include "../../Entity.h"

EntityTypeSelector::EntityTypeSelector(const EntityType *type) : types_({type}) {}

EntityTypeSelector::EntityTypeSelector(const std::initializer_list<const EntityType *> &types) : types_(types) {
}

bool EntityTypeSelector::select(const Entity *entity) const {
    return std::find(types_.begin(), types_.end(), entity->getType()) != types_.end();
}
