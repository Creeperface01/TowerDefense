#pragma once

#include <cstdint>

using VectorType = int16_t;
using Index2d = uint32_t;

inline Index2d make_index2d(VectorType x, VectorType y) {
    return (x << (sizeof(VectorType) * 8)) | y;
}