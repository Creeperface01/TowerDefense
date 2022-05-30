#include "Util.h"

std::optional<std::tuple<float, float>> MathUtil::quad(float a, float b, float c) {
    std::optional<std::tuple<float, float>> sol;

    if (std::abs(a) < 1e-6) {
        if (std::abs(b) < 1e-6) {
            if (std::abs(c) < 1e-6) {
                sol = {0.0f, 0.0f};
            }
        } else {
            sol = {-c / b, -c / b};
        }
    } else {
        float disc = b * b - 4 * a * c;
        if (disc >= 0) {
            disc = std::sqrtf(disc);
            a = 2 * a;

            sol = {(-b - disc) / a, (-b + disc) / a};
        }
    }

    return sol;
}

std::optional<Vector2f>
MathUtil::intercept(const Vector2f &src, const Vector2f &dst, const Vector2f &dst_motion, float v) {
    float tx = dst.x() - src.x();
    float ty = dst.y() - src.y();
    float tvx = dst_motion.x();
    float tvy = dst_motion.y();

    // Get quadratic equation components
    float a = tvx * tvx + tvy * tvy - v * v;
    float b = 2 * (tvx * tx + tvy * ty);
    float c = tx * tx + ty * ty;

    // Solve quadratic
    auto ts = quad(a, b, c); // See quad(), below

    // Find smallest positive solution
    std::optional<Vector2f> sol;
    if (ts) {
        float t0 = std::get<0>(ts.value());
        float t1 = std::get<1>(ts.value());

        float t = std::min(t0, t1);
        if (t < 0) t = std::max(t0, t1);
        if (t > 0) {
            sol = {
                    dst.x() + dst_motion.x() * t,
                    dst.y() + dst_motion.y() * t
            };
        }
    }

    return sol;
}
