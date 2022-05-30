#pragma once

#include "centurion.hpp"
#include "RenderSettings.h"

using namespace cen;

class game_basic_renderer {
private:
    cen::renderer_handle renderer_;

    RenderSettings settings_;

public:
    game_basic_renderer(
            RenderSettings settings,
            cen::renderer_handle renderer
    ) : settings_(settings), renderer_(renderer) {
    }

    template<class U>
    basic_rect<U> translate_meters(const basic_rect<U> &rect) noexcept {
        return {
                settings_.offsetX + (rect.x() * settings_.pixelsPerMeter),
                settings_.offsetY + (rect.y() * settings_.pixelsPerMeter),
                rect.width() * settings_.pixelsPerMeter,
                rect.height() * settings_.pixelsPerMeter,
        };
    }

    template<class U>
    basic_point<U> translate_meters(const basic_point<U> &point) noexcept {
        return {
                settings_.offsetX + (point.x() * settings_.pixelsPerMeter),
                settings_.offsetY + (point.y() * settings_.pixelsPerMeter),
        };
    }

    template<typename U>
    auto draw_rect_m(const basic_rect<U> &rect) noexcept -> result {
        return renderer_.draw_rect(translate_meters(rect));
    }

    template<typename U>
    auto draw_line_m(const basic_point<U> &start, const basic_point<U> &end) noexcept -> result {
        return renderer_.draw_line(translate_meters(start), translate_meters(end));
    }

    template<typename U>
    auto draw_circle_m(const basic_point<U> &position, const float radius) noexcept -> result {
        return renderer_.draw_circle(translate_meters(position), radius * settings_.pixelsPerMeter);
    }

    template<typename U>
    auto draw_point_m(const basic_point<U> &point) noexcept -> result {
        return renderer_.draw_point(translate_meters(point));
    }

    template<typename U>
    auto fill_rect_m(const basic_rect<U> &rect) noexcept -> result {
        auto t = translate_meters(rect);
        return renderer_.fill_rect(translate_meters(rect));
    }

    template<typename U>
    auto fill_circle_m(const fpoint center, const float radius) noexcept {
        return renderer_.fill_circle(translate_meters(center), radius * settings_.pixelsPerMeter);
    }

    //TODO: texture rendering
};