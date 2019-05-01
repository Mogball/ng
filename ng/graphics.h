#pragma once

#include "gl.h"
#include <Box2D/Box2D.h>
#include <array>

namespace ng {

    class Entity;
    class Window;

    class Graphics {
        enum Buffer {
            POSITION,

            BUFFER_COUNT
        };

        enum Uniform {
            MVP,
            TRANSLATE,
            ANGLE,

            UNIFORM_COUNT
        };

        enum Program {
            VERTEX,
            FRAGMENT,
            SHADER,

            PROGRAM_COUNT
        };

        float m_scale;

        std::array<GLuint, Buffer::BUFFER_COUNT> m_buffers;
        std::array<GLuint, Buffer::BUFFER_COUNT> m_attribs;
        std::array<GLuint, Uniform::UNIFORM_COUNT> m_uniforms;
        std::array<GLuint, Program::PROGRAM_COUNT> m_programs;

    public:
        Graphics(const Window &win, float scale);

        inline float scale() const { return m_scale; }

        void draw(const Entity &ent);
        void draw(const b2Body &body, const b2Fixture &fixture);
        void draw(const b2Body &body, const b2PolygonShape &polygon);
    };

}
