#pragma once

#include "../renderer/RenderSettings.h"
#include "../map/MapConfiguration.h"

#include <cstdint>

namespace Config {

    inline constexpr RenderSettings default_render_settings = {};

//    inline constexpr MapConfiguration default_map_configuration = {};

    MapConfiguration get_default_map_configuration(const std::string &terrain_file);
}