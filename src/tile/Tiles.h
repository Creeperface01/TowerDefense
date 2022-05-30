#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#pragma once

#include "Tile.h"

namespace Tiles {

    extern const Tile *const PATH;

    extern const Tile *const GROUND;

    extern const Tile *const BARRIER;

    extern const Tile *const PATH_TEST;

    void init();
}
#pragma clang diagnostic pop