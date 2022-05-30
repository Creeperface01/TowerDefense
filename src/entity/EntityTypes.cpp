#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-interfaces-global-init"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "EntityTypes.h"

#include "../world/World.h"
#include "attack/EntityBomb.h"
#include "common/EntityLaserBeam.h"
#include "attribute/EntityAttributes.h"

namespace EntityTypes {

    using func_r_type = std::unordered_map<const attribute_base *, void *>;

    extern const EntityType *const BOMB = EntityType::of<EntityBomb>(
            "bomb",
            1,
            1,
            []() -> func_r_type {
                return {
                        EntityAttributes::MAX_HEALTH->valuePair(10)
                };
            }
    );

    extern const EntityType *const LASER_BEAM = EntityType::of<EntityLaserBeam>(
            "laser_beam",
            0.6,
            0.6
    );

}
#pragma clang diagnostic pop