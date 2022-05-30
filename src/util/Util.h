#pragma once

#include <memory>

using unique_void_ptr = std::unique_ptr<void, void (*)(void const *)>;

template<typename T>
auto unique_void(T *ptr) -> unique_void_ptr {
    return unique_void_ptr(ptr, [](void const *data) {
        T const *p = static_cast<T const *>(data);
        delete p;
    });
}