#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "Tiles.h"

namespace Tiles {

    const Tile *const PATH = new Tile{"path", true};

    const Tile *const GROUND = new Tile("ground", false);

    const Tile *const BARRIER = new Tile("barrier", false);

    const Tile *const PATH_TEST = new Tile("path_test", true);

    void init() {

    }
}
#pragma clang diagnostic pop