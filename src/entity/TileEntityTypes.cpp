#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-interfaces-global-init"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "TileEntityTypes.h"

#include "common/TileEntitySpawner.h"
#include "common/TileEntityObjective.h"
#include "tile/TileEntityCanon.h"
#include "attribute/EntityAttributes.h"

namespace TileEntityTypes {

    using func_r_type = std::unordered_map<const attribute_base *, void *>;

    extern const EntityType *const SPAWNER = EntityType::of<TileEntitySpawner>(
            "spawner",
            1,
            1
    );

    extern const EntityType *const OBJECTIVE = EntityType::of<TileEntityObjective>(
            "objective",
            1,
            1,
            []() -> func_r_type {
                return {
                        EntityAttributes::MAX_HEALTH->valuePair(100)
                };
            }
    );

    extern const EntityType *const CANON = EntityType::of<TileEntityCanon>(
            "canon",
            1,
            1
    );

};
#pragma clang diagnostic pop