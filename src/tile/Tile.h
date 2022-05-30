#pragma once

#include <string>

class Tile final {
public:
    std::string_view name;

    bool passable;

    Tile(std::string_view name, bool passable);

    Tile(const Tile &) = delete;

    Tile &operator=(const Tile &) = delete;
};


