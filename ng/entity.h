#pragma once

#include "fvec.h"
#include <vector>

namespace ng {

    enum class Shape {
        SQUARE,
        TRIANGLE,
    };

    struct Geometry {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    };

    class Entity {
        fvec2   m_pos;
        float   m_angle;
        float   m_scale;

    public:
        inline Entity(fvec2 pos = {}, float angle = 0, float scale = 0) :
            m_pos(std::move(pos)),
            m_angle(std::move(angle)),
            m_scale(std::move(scale))
        {}

        inline fvec2 &pos()   { return m_pos; }
        inline float &angle() { return m_angle; }
        inline float &scale() { return m_scale; }

        inline const fvec2 &pos()   const { return m_pos; }
        inline const float &angle() const { return m_angle; }
        inline const float &scale() const { return m_scale; }
    };

}
