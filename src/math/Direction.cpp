#include "Direction.h"

Direction::Direction(uint8_t index, uint8_t opposite, Direction::AxisDirection axisDirection,
                     const Vector2i &unitVector) : index(index), opposite(opposite), axisDirection(axisDirection),
                                                   unitVector(unitVector) {}

uint8_t Direction::getIndex() const {
    return index;
}

Direction &Direction::getOpposite() const {
    return fromIndex(opposite);
}

Direction::AxisDirection Direction::getAxisDirection() const {
    return axisDirection;
}

const Vector2i &Direction::getUnitVector() const {
    return unitVector;
}

VectorType Direction::getXOffset() const {
    return unitVector.x();
}

VectorType Direction::getYOffset() const {
    return unitVector.y();
}

Direction &Direction::fromIndex(uint8_t i) {
    return *VALUES[i];
}

bool Direction::operator==(const Direction &other) const {
    return this == &other;
}

bool Direction::operator!=(const Direction &other) const {
    return this != &other;
}

const std::array<Direction *, 4> &Direction::values() {
    return VALUES;
}

const std::array<Direction::DiagonalPair, 4> &Direction::diagonal() {
    return DIAGONAL;
}

Direction Direction::DOWN = Direction(0, 1, AxisDirection::NEGATIVE, {0, -1}); // NOLINT(cert-err58-cpp)
Direction Direction::UP = Direction(1, 0, AxisDirection::POSITIVE, {0, 1}); // NOLINT(cert-err58-cpp)
Direction Direction::LEFT = Direction(2, 3, AxisDirection::POSITIVE, {-1, 0}); // NOLINT(cert-err58-cpp)
Direction Direction::RIGHT = Direction(3, 2, AxisDirection::NEGATIVE, {1, 0}); // NOLINT(cert-err58-cpp)

std::array<Direction *, 4> Direction::VALUES = {&Direction::DOWN, &Direction::UP, &Direction::LEFT, &Direction::RIGHT};

std::array<Direction::DiagonalPair, 4> Direction::DIAGONAL = {
        DiagonalPair{&Direction::DOWN, &Direction::LEFT},
        DiagonalPair{&Direction::LEFT, &Direction::UP},
        DiagonalPair{&Direction::UP, &Direction::RIGHT},
        DiagonalPair{&Direction::RIGHT, &Direction::DOWN}
};