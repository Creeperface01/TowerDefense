#include "Config.h"

namespace Config {

    MapConfiguration get_default_map_configuration(const std::string &terrain_file) {
        MapConfiguration configuration = {};

        configuration.terrain_ = MapConfiguration::Terrain::load_from_file(configuration, terrain_file);

        return configuration;
    }

}