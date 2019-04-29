#pragma once

#include <array>
#include <functional>

namespace ng {

    template<std::size_t N>
    using fvec = std::array<float, N>;

    template<std::size_t N, template<typename T> class Op>
    inline constexpr fvec<N> apply_op(const Op<float> &op, const fvec<N> &a, const fvec<N> &b) {
        fvec<N> r{};
        for (std::size_t i = 0; i < N; ++i) {
            r[i] = op(a[i], b[i]);
        }
        return r;
    }

    template<std::size_t N>
    inline constexpr fvec<N> operator+ (const fvec<N> &a, const fvec<N> &b) {
        return apply_op(std::plus<float>(), a, b);
    }

    template<std::size_t N>
    inline constexpr fvec<N> operator- (const fvec<N> &a, const fvec<N> &b) {
        return apply_op(std::minus<float>(), a, b);
    }

    typedef fvec<2> fvec2;
    typedef fvec<3> fvec3;
    typedef fvec<4> fvec4;

}
