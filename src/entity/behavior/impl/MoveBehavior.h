#pragma once

#include "../EntityBehavior.h"

class MoveBehavior : public EntityBehavior {
public:

    using EntityBehavior::EntityBehavior;

    void tick(uint32_t tick) override;

    bool shouldExecute() override;
};


