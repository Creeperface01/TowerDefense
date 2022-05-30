#pragma once

#include "../tile/Tile.h"
#include "../math/Vector.h"
#include "../entity/EntitySnapshot.h"
#include "../entity/TileEntitySnapshot.h"

#include <vector>
#include <memory>

class World;

class WorldSnapshot {
public:
    const World *obj_;

    const std::vector<std::unique_ptr<EntitySnapshot>> entities_;

    const std::vector<std::unique_ptr<TileEntitySnapshot>> tileEntities_;

//    const std::vector<std::pair<Vector2i, const Tile *>> tiles_;

    WorldSnapshot(
            const World *obj,
            std::vector<std::unique_ptr<EntitySnapshot>> entities,
            std::vector<std::unique_ptr<TileEntitySnapshot>> tileEntities
    );
};
