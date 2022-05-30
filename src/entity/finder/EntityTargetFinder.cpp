#include "EntityTargetFinder.h"

#include "../Entity.h"

EntityTargetFinder::EntityTargetFinder(
        World *world,
        std::optional<float> range,
        std::optional<EntitySelector *> selector
) :
        world_(world),
        range_(range),
        selector_(selector.value_or(nullptr)) {
}

bool EntityTargetFinder::matches(const Entity *source, const Entity *entity) const {
    if (entity == source) {
        return false;
    }

    if (selector_ != nullptr && !selector_->select(entity)) {
        return false;
    }

    if (range_.has_value()) {
        auto range = range_.value() * range_.value();

        if (source->getPosition().distanceSquared(entity->getPosition()) > range) {
            return false;
        }
    }

    return true;
}
