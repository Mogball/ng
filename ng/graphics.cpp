#include "graphics.h"
#include "linmath.h"
#include "window.h"

static constexpr auto VERT_CODE = R"glsl(
#version 150 core

in vec2 position;
in vec2 translate;
in float angle;
in float scale;

uniform mat4 mvp;

mat2 rot(float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return mat2(c, -s, s, c);
}

mat2 ratio(float scale) {
    return mat2(scale, 0, 0, scale);
}

void main() {
    gl_Position = mvp * vec4(translate + rot(angle) * ratio(scale) * position, 0.0, 1.0);
}
)glsl";

static constexpr auto FRAG_CODE = R"glsl(
#version 150 core

void main() {
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
)glsl";

namespace ng {

    Graphics::Graphics(const Window &win) {
        glGenBuffers(Buffer::BUFFER_COUNT, std::begin(m_buffers));

        auto &prog_vert = m_programs[Program::VERTEX];
        auto &prog_frag = m_programs[Program::FRAGMENT];
        auto &prog_shdr = m_programs[Program::SHADER];

        prog_vert = glCreateShader(GL_VERTEX_SHADER);
        prog_frag = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(prog_vert, 1, &VERT_CODE, nullptr);
        glShaderSource(prog_frag, 1, &FRAG_CODE, nullptr);
        glCompileShader(prog_vert);
        glCompileShader(prog_frag);

        prog_shdr = glCreateProgram();
        glAttachShader(prog_shdr, prog_vert);
        glAttachShader(prog_shdr, prog_frag);
        glLinkProgram(prog_shdr);
        glUseProgram(prog_shdr);

        constexpr GLuint divisors[] = { 0, 1, 1, 1 };
        constexpr GLuint sizes[]    = { 2, 2, 1, 1 };
        constexpr const char *names[] = {
            "position",
            "translate",
            "angle",
            "scale",
        };
        for (std::size_t i = 0; i < Buffer::BUFFER_COUNT; ++i) {
            auto &attrib = m_attribs[i];
            attrib = glGetAttribLocation(prog_shdr, names[i]);
            glBindBuffer(GL_ARRAY_BUFFER, m_buffers[i]);
            glEnableVertexAttribArray(attrib);
            glVertexAttribPointer(attrib, sizes[i], GL_FLOAT, GL_FALSE, 0, 0);
            glVertexAttribDivisor(attrib, divisors[i]);
        }

        m_uniforms[Uniform::MVP] = glGetUniformLocation(prog_shdr, "mvp");

        float r = static_cast<float>(win.width()) / win.height();
        mat4x4 mvp;
        mat4x4_ortho(mvp, -r, r, -1, 1, 0, 1);
        glUniformMatrix4fv(m_uniforms[Uniform::MVP], 1, GL_FALSE, reinterpret_cast<GLfloat *>(mvp));
    }

    void Graphics::draw(const Geometry &geo, const std::vector<Entity> &ents) {
        glBindBuffer(GL_ARRAY_BUFFER, m_buffers[Buffer::POSITION]);
        glBufferData(GL_ARRAY_BUFFER, byte_size(geo.vertices), geo.vertices.data(), GL_STATIC_DRAW);

        std::vector<float> pos{};
        std::vector<float> angle{};
        std::vector<float> scale{};
        pos.reserve(ents.size());
        angle.reserve(ents.size());
        scale.reserve(ents.size());
        for (const auto &ent : ents) {
            pos.push_back(ent.pos()[0]);
            pos.push_back(ent.pos()[1]);
            angle.push_back(ent.angle());
            scale.push_back(ent.scale());
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_buffers[Buffer::TRANSLATE]);
        glBufferData(GL_ARRAY_BUFFER, byte_size(pos), pos.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, m_buffers[Buffer::ANGLE]);
        glBufferData(GL_ARRAY_BUFFER, byte_size(angle), angle.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, m_buffers[Buffer::SCALE]);
        glBufferData(GL_ARRAY_BUFFER, byte_size(scale), scale.data(), GL_STATIC_DRAW);

        const auto &indices = geo.indices;
        glDrawElementsInstanced(GL_TRIANGLE_FAN, indices.size(), GL_UNSIGNED_INT, indices.data(), ents.size());
    }

}
