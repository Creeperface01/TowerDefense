#pragma once

#include <cstdint>
#include <centurion.hpp>

struct RenderSettings {

    float pixelsPerMeter = 14;

    float offsetX = 0;
    float offsetY = 0;

    cen::iarea gameWindowSize = cen::window::default_size();

    cen::iarea menuWindowSize = cen::window::default_size();
};