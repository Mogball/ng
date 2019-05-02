#include "utility.h"
#include <cmath>

namespace ng {

    std::vector<b2Vec2> make_circle(std::size_t vertex_count) {
        std::vector<b2Vec2> ret;
        ret.reserve(vertex_count);
        double angle_delta = 2 * M_PI / vertex_count;
        for (double angle = 0; angle < 2 * M_PI; angle += angle_delta) {
            ret.emplace_back(std::cos(angle), std::sin(angle));
        }
        return ret;
    }

}
