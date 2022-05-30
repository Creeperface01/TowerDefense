#include "WorldSnapshot.h"

#include <utility>

WorldSnapshot::WorldSnapshot(
        const World *obj,
        std::vector<std::unique_ptr<EntitySnapshot>> entities,
        std::vector<std::unique_ptr<TileEntitySnapshot>> tileEntities
) : obj_(obj),
    entities_(std::move(entities)),
    tileEntities_(std::move(tileEntities)) {}
