#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "EntityAttributes.h"

#include <limits>

namespace EntityAttributes {

    const EntityAttribute<uint16_t> *const MAX_HEALTH = new EntityAttribute<uint16_t>(
            "max_health",
            0,
            std::numeric_limits<uint16_t>::max(),
            100
    );

    const EntityAttribute<float> *const SPEED = new EntityAttribute<float>(
            "max_health",
            0,
            100,
            1
    );

    const EntityAttribute<float> *const SHOOT_RANGE = new EntityAttribute<float>(
            "max_health",
            0,
            100,
            10
    );

    extern const std::vector<const void *> VALUES = {
            static_cast<const void *>(MAX_HEALTH),
            static_cast<const void *>(SPEED),
            static_cast<const void *>(SHOOT_RANGE)
    };
}

#pragma clang diagnostic pop