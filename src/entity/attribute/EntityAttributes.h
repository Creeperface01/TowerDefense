#pragma once

#include "EntityAttribute.h"

#include <cstdint>
#include <vector>

namespace EntityAttributes {

    extern const EntityAttribute<uint16_t> *const MAX_HEALTH;

    extern const EntityAttribute<float> *const SPEED;

    extern const EntityAttribute<float> *const SHOOT_RANGE;

    extern const std::vector<const void *> VALUES;
}
