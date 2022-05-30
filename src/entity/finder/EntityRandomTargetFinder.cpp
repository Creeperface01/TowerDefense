#include "EntityRandomTargetFinder.h"

#include "../../world/World.h"

std::optional<Entity *> EntityRandomTargetFinder::find(Entity *source) {
    for (const auto &item: world_->getEntities()) {
        if (matches(source, item.second.get())) {
            return {item.second.get()};
        }
    }

    return std::nullopt;
}
