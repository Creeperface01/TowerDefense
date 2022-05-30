#include "Graphics.h"

#include "GameRenderer.h"
#include "../util/Fps.h"

void Graphics::run(const RenderSettings &settings) {
    cen::library centurion;

    Fps fps;

    cen::event event;
    bool running = true;

    while (running) {
        while (event.poll()) {
            // Check if the user wants to quit the application
            if (event.is<cen::quit_event>()) {
                running = false;
                break;
            }

            auto sdlEvent = *event.data();
//            menu.onEvent(sdlEvent);
        }

//        renderer.clear_with(cen::colors::dark_gray);

//        menu.drawAll();

//        renderer.present();

        fps.next();
    }

    // Make the window invisible again, this might not be necessary, but it doesn't hurt
//    window.hide();

}
