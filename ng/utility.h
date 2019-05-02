#pragma once

#include <Box2D/Box2D.h>
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

    std::vector<b2Vec2> make_circle(std::size_t vertex_count);

}
