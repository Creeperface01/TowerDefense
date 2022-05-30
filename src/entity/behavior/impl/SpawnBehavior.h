#pragma once

#include "../EntityBehavior.h"
#include "../../EntityType.h"

#include <cstdint>

class SpawnBehavior : public EntityBehavior {
private:
    uint32_t spawn_interval_;
    const EntityType *entity_type_;

    int32_t last_spawn_tick_ = -1000000;

public:
    SpawnBehavior(
            Entity *e,
            uint32_t spawn_interval,
            const EntityType *entityType
    );

    bool startExecuting() override;

    bool canContinue() override;

    bool shouldExecute() override;
};
