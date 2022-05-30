#include "Tile.h"

#include <iostream>

Tile::Tile(std::string_view name, bool passable) : name(name), passable(passable) {
}
