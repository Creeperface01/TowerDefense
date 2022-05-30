#pragma once

#include <array>
#include <tuple>

#include "Vector.h"

class Direction {
public:
    static Direction DOWN;
    static Direction UP;
    static Direction LEFT;
    static Direction RIGHT;

    enum class AxisDirection {
        POSITIVE = 1,
        NEGATIVE = -1
    };

    enum class Axis {
        X,
        Y
    };

private:
    using DiagonalPair = std::pair<Direction *, Direction *>;

    static std::array<Direction *, 4> VALUES;

    static std::array<DiagonalPair, 4> DIAGONAL;

    uint8_t index;

    uint8_t opposite;

    AxisDirection axisDirection;

    Vector2i unitVector;

    Direction(uint8_t index, uint8_t opposite, AxisDirection axisDirection, const Vector2i &unitVector);

public:
    static Direction &fromIndex(uint8_t index);

    static const std::array<Direction *, 4> &values();

    static const std::array<DiagonalPair, 4> &diagonal();

    Direction(const Direction &) = delete;

    Direction &operator=(const Direction &) = delete;

    [[nodiscard]] uint8_t getIndex() const;

    [[nodiscard]] Direction &getOpposite() const;

    [[nodiscard]] AxisDirection getAxisDirection() const;

    [[nodiscard]] const Vector2i &getUnitVector() const;

    [[nodiscard]] VectorType getXOffset() const;

    [[nodiscard]] VectorType getYOffset() const;

    bool operator==(const Direction &other) const;

    bool operator!=(const Direction &other) const;

};

template<typename T>
vector2<T> vector2<T>::offset(const Direction &direction, VectorType step) const {
    return vector2<T>{
            static_cast<T>(this->x() + (direction.getXOffset() * step)),
            static_cast<T>(this->y() + (direction.getYOffset() * step))
    };
}
