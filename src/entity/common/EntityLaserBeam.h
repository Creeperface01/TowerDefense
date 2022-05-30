#pragma once

#include "../Entity.h"

class EntityLaserBeam : public Entity {

public:
    using Entity::Entity;

    void init() override;

    void tick(uint32_t tick) override;
};
