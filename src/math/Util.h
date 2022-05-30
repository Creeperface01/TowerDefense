#pragma once

#include "Vector.h"

#include <optional>
#include <tuple>

namespace MathUtil {

    std::optional<std::tuple<float, float>> quad(float a, float b, float c);

    std::optional<Vector2f> intercept(const Vector2f &src, const Vector2f &dst, const Vector2f &dst_motion, float v);

};
