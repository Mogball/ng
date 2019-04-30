#pragma once

#include <type_traits>
#include <vector>

namespace ng {

    template<typename E>
    constexpr auto underlying(E e) noexcept {
        return static_cast<std::underlying_type_t<E>>(e);
    }

    template<typename T>
    constexpr auto byte_size(const std::vector<T> &v) {
        return v.size() * sizeof(T);
    }

}
