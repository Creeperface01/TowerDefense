#pragma once

#include <centurion.hpp>

#include "RenderSettings.h"

class MenuRenderer {

private:
    cen::window window_;

public:

    explicit MenuRenderer(
            RenderSettings settings
    );

    void render();
};
