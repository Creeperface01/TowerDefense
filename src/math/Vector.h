#pragma once

#include "../util/Types.h"

#include <cstdint>
#include <cmath>
#include <psst/math/vector.hpp>

class Direction;

template<typename T>
class vector2 : public psst::math::vector<T, 2> {
private:
    using this_type = vector2<T>;

public:

    using psst::math::vector<T, 2>::vector;

    [[nodiscard]] this_type offset(const Direction &direction, VectorType step = 1) const;

    [[nodiscard]] this_type add(T x, T y) const {
        return this_type{
                static_cast<T>(this->x() + x),
                static_cast<T>(this->y() + y)
        };
    }

    [[nodiscard]] this_type add(const this_type &vec) const {
        return add(vec.x(), vec.y());
    }

    [[nodiscard]] Index2d index2d() const {
        return make_index2d(this->x(), this->y());
    }

    [[nodiscard]] auto distanceSquared(const this_type &other) const {
        return (this->x() - other.x()) * (this->x() - other.x()) + (this->y() - other.y()) * (this->y() - other.y());
    }

    [[nodiscard]] auto distance(const this_type &other) const {
        return std::sqrt(distanceSquared(other));
    }

    std::partial_ordering operator<=>(const this_type &other) const {
        return index2d() <=> other.index2d();
    }

    [[nodiscard]] this_type ceil() const {
        return {std::ceil(this->x()), std::ceil(this->y())};
    }

    [[nodiscard]] this_type floor() const {
        return {std::floor(this->x()), std::floor(this->y())};
    }

    [[nodiscard]] vector2<VectorType> toInt() const {
        return {
                static_cast<VectorType>(std::floor(this->x())),
                static_cast<VectorType>(std::floor(this->y()))
        };
    }

    [[nodiscard]] vector2<float> toFloat() const {
        return {
                static_cast<float>(this->x()),
                static_cast<float>(this->y())
        };
    }

    [[nodiscard]] float angleBetween(const this_type &other) const {
        return std::acos(std::min(std::max(
                static_cast<float>(this->normalize().dot(other.normalize())), -1.0f
        ), 1.0f));
    }

    [[nodiscard]] float lengthSquared() const {
        return static_cast<float>(this->x()) * static_cast<float>(this->x()) +
               static_cast<float>(this->y()) * static_cast<float>(this->y());
    }

    [[nodiscard]] float length() const {
        return std::sqrt(lengthSquared());
    }
};

using Vector2i = vector2<VectorType>;
//using Vector3i = vector<int32_t, 3>;

using Vector2f = vector2<float>;
//using Vector3f = vector<float, 3>;

namespace std {
    template<>
    struct hash<Vector2i> {
        size_t operator()(const Vector2i &x) const;
    };
}