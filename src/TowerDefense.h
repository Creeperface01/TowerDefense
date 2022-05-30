#pragma once

#include "map/MapConfiguration.h"

class TowerDefense {

public:
    TowerDefense();

    enum class RunMode {
        BLOCKING,
        ASYNC
    };

    void start(const MapConfiguration &configuration, RunMode mode) const;
};


