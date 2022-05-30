#pragma once

#include <type_traits>
#include <optional>

#include "Vector.h"

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<typename T> requires Arithmetic<T>
class BoundingBox {
    using Vec2 = vector2<T>;

private:
    Vec2 min;
    Vec2 max;

public:
    BoundingBox() {
        min.zero();
        max.zero();
    }

    BoundingBox(const Vector2f &pos1, const Vector2f &pos2) {
        this->min.x() = std::min(pos1.x(), pos2.x());
        this->min.y() = std::min(pos1.y(), pos2.y());

        this->max.x() = std::max(pos1.x(), pos2.x());
        this->max.y() = std::max(pos1.y(), pos2.y());
    }

    BoundingBox(const Vector2i &pos1, const Vector2i &pos2) {
        this->min.x() = std::min(pos1.x(), pos2.x());
        this->min.y() = std::min(pos1.y(), pos2.y());

        this->max.x() = std::max(pos1.x(), pos2.x());
        this->max.y() = std::max(pos1.y(), pos2.y());
    }

    BoundingBox(
            float minX,
            float minY,
            float maxX,
            float maxY
    ) {
        this->min = {minX, minY};
        this->max = {maxX, maxY};
    }

    BoundingBox(
            int32_t minX,
            int32_t minY,
            int32_t maxX,
            int32_t maxY
    ) {
        this->min = {minX, minY};
        this->max = {maxX, maxY};
    }

    Vec2 getMin() const {
        return min;
    }

    Vec2 getMax() const {
        return max;
    }

    T getMinX() const {
        return min.x();
    }

    T getMinY() const {
        return min.y();
    }

    T getMaxX() const {
        return max.x();
    }

    T getMaxY() const {
        return max.y();
    }

    BoundingBox clone() const {
        return {min, max};
    }

    BoundingBox &setBounds(
            T minX,
            T minY,
            T maxX,
            T maxY
    ) {
        min.x() = minX;
        min.y() = minY;

        max.x() = maxX;
        max.y() = maxY;
    }

    BoundingBox &setBounds(
            const Vec2 &pos1,
            const Vec2 &pos2
    ) {
        min.x() = std::min(pos1.x(), pos2.x());
        min.y() = std::min(pos1.y(), pos2.y());

        max.x() = std::max(pos1.x(), pos2.x());
        max.y() = std::max(pos1.y(), pos2.y());
    }

//    BoundingBox addCoord(
//            T x,
//            T y
//    ) const {
//        return {}
//    }
//
//    BoundingBox addCoord(const Vector2f &vec) const {
//        return addCoord(vec.x(), vec.y());
//    }

    BoundingBox grow(T x, T y) const {
        return {min - Vec2{x, y}, max + Vec2{x, y}};
    }

    BoundingBox grow(const Vec2 &vec) const {
        return grow(vec.x(), vec.y());
    }

    BoundingBox &expand(T x, T y) {
        min.x() -= x;
        min.y() -= y;

        max.x() += x;
        max.y() += y;

        return *this;
    }

    BoundingBox &expand(const Vec2 &vec) {
        min -= vec;
        max += vec;

        return *this;
    }

    BoundingBox &offset(const Vec2 &vec) {
        min += vec;
        max += vec;

        return *this;
    }

    BoundingBox &offset(T x, T y) {
        return offset(Vec2{x, y});
    }

    BoundingBox shrink(T x, T y) const {
        return {
                min.x() + x,
                min.y() + y,
                max.x() - x,
                max.y() - y
        };
    }

    BoundingBox &contract(const Vec2 &vec) {
        min += vec;
        max -= vec;

        return *this;
    }

    BoundingBox &contract(T x, T y) {
        return contract(Vec2{x, y});
    }

    bool intersectsWith(const BoundingBox &bb) const {
        if (bb.getMaxY() > this->getMinY() && bb.getMinY() < this->getMaxY()) {
            return bb.getMaxX() > this->getMinX() && bb.getMinX() < this->getMaxX();
        }

        return false;
    }

    bool isVectorInside(const Vec2 &vec) const {
        return vec.x() >= this->getMinX()
               && vec.x() <= this->getMaxX()
               && vec.y() >= this->getMinY()
               && vec.y() <= this->getMaxY();
    }

    T getAverageEdgeLength() const {
        return (this->getMaxX() - this->getMinX() + this->getMaxY() - this->getMinY()) / 2;
    }

    std::optional<Vec2> getIntermediateWithXValue(const Vec2 &pos1, const Vec2 &pos2, T x) {
        T xDiff = pos2.x() - pos1.x();
        T yDiff = pos2.y() - pos1.y();

        if (xDiff * xDiff < 0.0000001) {
            return std::nullopt;
        }

        T f = (x - pos1.x()) / xDiff;
        if (f < 0 || f > 1) {
            return std::nullopt;
        } else {
            return {pos1.x() + xDiff * f, pos1.y() + yDiff * f};
        }
    }

    std::optional<Vec2> getIntermediateWithYValue(const Vec2 &pos1, const Vec2 &pos2, T y) {
        T xDiff = pos2.x() - pos1.x();
        T yDiff = pos2.y() - pos1.y();

        if (yDiff * yDiff < 0.0000001) {
            return std::nullopt;
        }

        T f = (y - pos1.y()) / yDiff;

        if (f < 0 || f > 1) {
            return std::nullopt;
        } else {
            return {pos1.x() + xDiff * f, pos1.y() + yDiff * f};
        }
    }

    void calculateIntercept(const Vec2 &pos1, const Vec2 &pos2) const {
        auto v1 = getIntermediateWithXValue(pos1, pos2, this->getMinX());
        auto v2 = getIntermediateWithXValue(pos1, pos2, this->getMaxX());
        auto v3 = getIntermediateWithYValue(pos1, pos2, this->getMinY());
        auto v4 = getIntermediateWithYValue(pos1, pos2, this->getMaxY());

        if (v1.has_value() && !this->isVectorInside(v1)) {
            v1 = std::nullopt;
        }

        if (v2.has_value() && !this->isVectorInside(v2)) {
            v2 = std::nullopt;
        }

        if (v3.has_value() && !this->isVectorInside(v3)) {
            v3 = std::nullopt;
        }

        if (v4.has_value() && !this->isVectorInside(v4)) {
            v4 = std::nullopt;
        }

        std::optional<Vec2> vector = std::nullopt;

        if (v1.has_value()) {
            vector = v1;
        }

        using namespace psst::math::expr;

        if (v2.has_value() && (!vector.has_value() || distance_square(pos1, v2) <
                                                      distance_square(pos1, vector.value()))) {
            vector = v2;
        }

        if (v3.has_value() && (!vector.has_value() || distance_square(pos1, v3) <
                                                      distance_square(pos1, vector.value()))) {
            vector = v3;
        }

        if (v4.has_value() && (!vector.has_value() || distance_square(pos1, v4) <
                                                      distance_square(pos1, vector.value()))) {
            vector = v4;
        }

        if (!vector.has_value()) {
//            return std::nullopt;
        }

        int face = -1;

        if (vector == v1) {
            face = 4;
        } else if (vector == v2) {
            face = 5;
        } else if (vector == v3) {
            face = 0;
        } else if (vector == v4) {
            face = 1;
        }

//        return MovingObjectPosition.fromBlock(Vector3i.ZERO, face, vector);
    }

    T getWidth() const {
        return max.x() - min.x();
    }

    T getHeight() const {
        return max.y() - min.y();
    }

    Vec2 getCenter() const {
        return {
                (max.x() + min.x()) / 2,
                (max.y() + min.y()) / 2
        };
    }
};

using AABB = BoundingBox<float>;

