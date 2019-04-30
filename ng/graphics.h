#pragma once

#include "entity.h"
#include "gl.h"
#include "utility.h"
#include <array>

namespace ng {

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

        std::array<GLuint, Buffer::BUFFER_COUNT> m_buffers;
        std::array<GLuint, Buffer::BUFFER_COUNT> m_attribs;
        std::array<GLuint, Uniform::UNIFORM_COUNT> m_uniforms;
        std::array<GLuint, Program::PROGRAM_COUNT> m_programs;

    public:
        Graphics(const Window &win);

        void draw(const Entity &ent);
    };

}
