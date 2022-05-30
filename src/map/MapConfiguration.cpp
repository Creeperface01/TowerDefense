#include "MapConfiguration.h"

#include "../tile/Tiles.h"

#include <fstream>
#include <exception>
#include <unordered_map>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-emplace"

std::shared_ptr<MapConfiguration::Terrain> MapConfiguration::Terrain::load_from_file(
        MapConfiguration &configuration,
        const std::string &path
) {
    std::ifstream ifs(path);

    if (!ifs.good()) {
        throw std::runtime_error("Could not read input file");
    }

    static const std::unordered_map<char, const Tile *const> tile_map = {
            {'X', Tiles::GROUND},
            {'#', Tiles::PATH}
    };

    std::string line;

    std::getline(ifs, line);
    configuration.width_ = std::stoi(line);

    std::getline(ifs, line);
    configuration.height_ = std::stoi(line);

    auto terrain = std::make_shared<MapConfiguration::Terrain>(
            new const Tile *[configuration.height_ * configuration.width_]
    );

    VectorType y = 0;
    while (std::getline(ifs, line)) {
        int x = 0;
        for (; x < line.size(); ++x) {
            if (x > configuration.width_) {
                throw std::runtime_error("Incorrect map width");
            }

            auto c = line[x];

            if (tile_map.contains(c)) {
                auto pair = tile_map.find(c);

                terrain->tiles_[y * configuration.width_ + x] = pair->second;
            } else {

                switch (c) {
                    case '-':
                        terrain->tiles_[y * configuration.width_ + x] = Tiles::PATH;
                        terrain->spawn_positions_.push_back(Vector2i{static_cast<VectorType>(x), y});
                        break;
                    case 'O':
                        terrain->tiles_[y * configuration.width_ + x] = Tiles::GROUND;
                        terrain->objective_positions_.push_back(Vector2i{static_cast<VectorType>(x), y});
                        break;
                    default:
                        throw std::runtime_error("Unknown field type");
                }
            }
        }

        if (x < configuration.width_) {
            throw std::runtime_error("Incorrect map width");
        }

        y++;
    }

    return terrain;
}

#pragma clang diagnostic pop

MapConfiguration::Terrain::Terrain(const Tile **tiles) {
    this->tiles_ = std::shared_ptr<const Tile *[]>(tiles);
}
