#pragma once

#include "../util/Types.h"
#include "../tile/Tiles.h"
#include "../math/Vector.h"

#include <vector>
#include <memory>
#include <string>

class MapConfiguration {
public:
//    MapConfiguration(const MapConfiguration &configuration);

    uint8_t width_ = 30, height_ = 20;

    uint16_t tick_rate_ = 20;

    float movement_speed_ = 1;
    float attack_speed_ = 1;

    float entity_health_ = 1;
    float objective_health_ = 1;

    float economy_rate_ = 1;

    uint32_t spawning_rate_ = 10;

    class Terrain {
    public:
        std::shared_ptr<const Tile *[]> tiles_;

        std::vector<Vector2i> spawn_positions_;

        std::vector<Vector2i> objective_positions_;

        static std::shared_ptr<Terrain> load_from_file(MapConfiguration &configuration, const std::string &path);

        explicit Terrain(const Tile *tiles[]);
    };

    std::shared_ptr<Terrain> terrain_;

};
