#include "TowerDefense.h"
#include "renderer/menu/MainMenu.h"
#include "util/Fps.h"
#include "map/MapConfiguration.h"
#include "world/World.h"
#include "renderer/GameRenderer.h"
#include "renderer/game_basic_renderer.h"
#include "util/Config.h"

#include <chrono>
#include <centurion.hpp>
#include <sdlgui/screen.h>
#include <thread>
#include <functional>

void render_window(
        cen::window_handle &window,
        cen::renderer_handle &renderer,
        const std::function<bool(cen::event &)> &callback
) {
    window.show();

    Fps fps(30);

    bool running = true;

    cen::event event;
    while (running) {
        running = callback(event);

        renderer.present();

        fps.next();
    }

    // Make the window invisible again, this might not be necessary, but it doesn't hurt
    window.hide();
}

TowerDefense::TowerDefense() {
    cen::library centurion;

    auto size = cen::window::default_size();
    auto [window, renderer] = cen::make_window_and_renderer(size);

    cen::window_handle window_handle(window);
    cen::renderer_handle renderer_handle(renderer);

    renderer.set_translation_viewport(cen::frect({1, 1}));

    auto menu = MainMenu(
            *this,
            window,
            sdlgui::Vector2i(size.width, size.height),
            "window"
    );

    window.show();

    render_window(
            window_handle,
            renderer_handle,
            [&renderer_handle, &menu](cen::event &event) {
                while (event.poll()) {
                    // Check if the user wants to quit the application
                    if (event.is<cen::quit_event>()) {
                        return false;
                    }

                    auto sdlEvent = *event.data();
                    menu.onEvent(sdlEvent);
                }

                renderer_handle.clear_with(cen::colors::dark_gray);

                menu.drawAll();

                return true;
            }
    );

//    Fps fps;

//    cen::event event;
//    bool running = true;
//
//    while (running) {
//        while (event.poll()) {
//            // Check if the user wants to quit the application
//            if (event.is<cen::quit_event>()) {
//                running = false;
//                break;
//            }
//
//            auto sdlEvent = *event.data();
//            menu.onEvent(sdlEvent);
//        }
//
//        renderer.clear_with(cen::colors::dark_gray);
//
//        menu.drawAll();
//
//        renderer.present();
//
//        fps.next();
//    }

//    // Make the window invisible again, this might not be necessary, but it doesn't hurt
//    window.hide();
}

void TowerDefense::start(const MapConfiguration &configuration, RunMode mode) const {
    World world(configuration);
    std::atomic<bool> running = true;

    auto tick = [&world, &configuration, &running]() {

        float ms = 1000.0f / static_cast<float>(configuration.tick_rate_);

        while (running) {
            auto begin = std::chrono::steady_clock::now();

            world.tick();

            auto end = std::chrono::steady_clock::now();

            auto diff = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

            if (ms - diff > 1) {
                cen::thread::sleep(cen::milliseconds<cen::u32>{static_cast<cen::u32>(ms - diff)});
            }
        }
    };

    std::thread thread(tick);

//    if(mode == RunMode::ASYNC) {
//        std::thread thread(tick);
//    } else {
//        tick();
//    }

    RenderSettings render_settings = Config::default_render_settings;

    cen::iarea size = {
            .width = static_cast<int>(static_cast<float>(configuration.width_) * render_settings.pixelsPerMeter),
            .height = static_cast<int>(static_cast<float>(configuration.height_) * render_settings.pixelsPerMeter)
    };
    auto [window, renderer] = cen::make_window_and_renderer(size);

    window.set_title("Tower Defense");

    cen::window_handle window_handle(window);
    cen::renderer_handle renderer_handle(renderer);

    renderer.set_translation_viewport(cen::frect({render_settings.offsetX, render_settings.offsetY}));

    game_basic_renderer game_basic_renderer(render_settings, renderer_handle);


    GameRenderer game_renderer(renderer_handle, game_basic_renderer, world);

    render_window(
            window_handle,
            renderer_handle,
            [
                    &render_settings,
                    &renderer_handle,
                    &game_renderer,
                    &window_handle,
                    &world
            ](cen::event &event) {
                while (event.poll()) {
                    // Check if the user wants to quit the application
                    if (event.is<cen::quit_event>()) {
                        return false;
                    }

                    if (event.is<cen::window_event>()) {
                        auto window_event = event.get<cen::window_event>();

                        if (window_event.event_id() == cen::window_event_id::close) {
                            return false;
                        }
                    }

                    if (event.is<cen::mouse_button_event>()) {
                        auto mouse_event = event.get<cen::mouse_button_event>();

                        if (mouse_event.window_id() == window_handle.id()) {
                            Vector2i world_coords = {
                                    static_cast<VectorType>(
                                            static_cast<float>(mouse_event.x()) / render_settings.pixelsPerMeter
                                    ),
                                    static_cast<VectorType>(
                                            static_cast<float>(mouse_event.y()) / render_settings.pixelsPerMeter
                                    )
                            };

                            world.addAction([world_coords](World &w) {
                                auto tile = w.getTile(world_coords);

                                if (tile != Tiles::GROUND) {
                                    return;
                                }

                                if (w.getTileEntity(world_coords).has_value()) {
                                    return;
                                }

                                w.createEntity(
                                        TileEntityTypes::CANON,
                                        world_coords
                                );
                            });
                        }
                    }
                }

                renderer_handle.clear_with(cen::colors::dark_gray);

                game_renderer.render();

                return true;
            });

    running = false;
}
