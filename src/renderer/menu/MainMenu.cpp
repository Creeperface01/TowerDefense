#include "MainMenu.h"
#include "../../TowerDefense.h"
#include "../../util/Config.h"

#include <sdlgui/window.h>
#include <sdlgui/screen.h>
#include <sdlgui/layout.h>
#include <sdlgui/label.h>
#include <sdlgui/checkbox.h>
#include <sdlgui/button.h>
#include <sdlgui/toolbutton.h>
#include <sdlgui/popupbutton.h>
#include <sdlgui/combobox.h>
#include <sdlgui/dropdownbox.h>
#include <sdlgui/progressbar.h>
#include <sdlgui/entypo.h>
#include <sdlgui/messagedialog.h>
#include <sdlgui/textbox.h>
#include <sdlgui/slider.h>
#include <sdlgui/imagepanel.h>
#include <sdlgui/imageview.h>
#include <sdlgui/vscrollpanel.h>
#include <sdlgui/colorwheel.h>
#include <sdlgui/graph.h>
#include <sdlgui/tabwidget.h>
#include <sdlgui/switchbox.h>
#include <sdlgui/formhelper.h>

#include <iostream>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "VirtualCallInCtorOrDtor"

#include "portable-file-dialogs.h"

#include <iostream>
#include <filesystem>

MainMenu::MainMenu(
        const TowerDefense &game,
        cen::window &win,
        const sdlgui::Vector2i &size,
        const std::string &caption,
        bool resizable,
        bool fullscreen
) : Screen(win.get(), size, caption, resizable, fullscreen) {

    auto &nwindow = window("Main Menu", sdlgui::Vector2i{0, 500});
    nwindow.center();
    nwindow.withLayout<sdlgui::GroupLayout>();

    nwindow
            .button(
                    "New Game",
                    [game] {
                        pfd::open_file open_file(
                                "Choose map configuration file",
                                std::filesystem::current_path().string()
                        );

                        auto paths = open_file.result();

                        if (paths.empty()) {
                            return;
                        }

                        auto path = paths.front();

                        game.start(
                                Config::get_default_map_configuration(path),
                                TowerDefense::RunMode::BLOCKING
                        );
                    }
            );

    nwindow.button(
            "Quit",
            [] {
                cen::event::push(cen::quit_event{});
            }
    );

    performLayout(get_renderer(win).get());
}

#pragma clang diagnostic pop
