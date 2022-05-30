#pragma once

#include "../EntityBehavior.h"

class AttackBehavior : public EntityBehavior {

public:
    using EntityBehavior::EntityBehavior;

    void tick(uint32_t tick) override;

    bool shouldExecute() override;
};
