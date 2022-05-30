#include "EntityPredicateSelector.h"

#include <utility>

EntityPredicateSelector::EntityPredicateSelector(
        std::function<bool(const Entity *)> predicate
) : predicate(std::move(
        predicate)) {}

bool EntityPredicateSelector::select(const Entity *entity) const {
    return predicate(entity);
}
