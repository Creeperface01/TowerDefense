#pragma once

#include "../Entity.h"

class EntityBomb : public Entity {

public:
    using Entity::Entity;

    void init() override;
};
