#include "SpawnBehavior.h"

#include "../../Entity.h"
#include "../../../world/World.h"

#include <iostream>

SpawnBehavior::SpawnBehavior(
        Entity *e,
        uint32_t spawn_interval,
        const EntityType *entityType
) :
        EntityBehavior(e),
        spawn_interval_(spawn_interval),
        entity_type_(entityType) {}

bool SpawnBehavior::startExecuting() {
    entity_->world_.createEntity(
            this->entity_type_,
            this->entity_->getPosition()
    );

    last_spawn_tick_ = static_cast<int32_t>(entity_->world_.getTick());

    return true;
}

bool SpawnBehavior::canContinue() {
    return false;
}

bool SpawnBehavior::shouldExecute() {
    return static_cast<int32_t>(entity_->getWorld().getTick()) - last_spawn_tick_ >= spawn_interval_;
}
