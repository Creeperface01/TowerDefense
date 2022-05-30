#pragma once

#include "../EntityBehavior.h"
#include "../../finder/EntityTargetFinder.h"
#include "../../EntityType.h"

#include <functional>
#include <memory>

class ShootOnMovingTargetBehavior : public EntityBehavior {
private:
    std::unique_ptr<EntityTargetFinder> finder_;

    uint32_t shooting_frequency_;
    uint32_t last_shoot_tick_ = 0;

    const EntityType *projectile_type_;

    float projectile_speed_;

public:
    ShootOnMovingTargetBehavior(
            Entity *e,
            EntityTargetFinder *finder,
            uint32_t shooting_frequency,
            const EntityType *projectile_type,
            float projectile_speed
    );

    bool startExecuting() override;

    bool shouldExecute() override;

    virtual ~ShootOnMovingTargetBehavior();
};
