#pragma once

#include <centurion.hpp>
#include <sdlgui/screen.h>

class TowerDefense;

class MainMenu : public sdlgui::Screen {
public:
    MainMenu(
            const TowerDefense &game,
            cen::window &window,
            const sdlgui::Vector2i &size,
            const std::string &caption,
            bool resizable = true,
            bool fullscreen = false
    );
};


