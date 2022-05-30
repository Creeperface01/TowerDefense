#include "MenuRenderer.h"

#include "menu/MainMenu.h"

MenuRenderer::MenuRenderer(RenderSettings settings) :
        window_(cen::window(
                "Main Menu",
                settings.menuWindowSize,
                cen::window::default_flags()
        )) {

}

void MenuRenderer::render() {
//    auto menu = MainMenu(
//            window_,
//            {300, 1000},
//            "Main Menu",
//            true,
//            false
//    );
}
