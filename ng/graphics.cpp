#include "graphics.h"
#include "linmath.h"
#include "window.h"

static constexpr auto WORLD_SCALE = 0.1;

static constexpr auto VERT_CODE = R"glsl(
#version 150 core

in vec2 position;

uniform vec2 translate;
uniform float angle;
uniform mat4 mvp;

mat2 rot(float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return mat2(c, -s, s, c);
}

void main() {
    gl_Position = mvp * vec4(translate + rot(angle) * position, 0.0, 1.0);
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

        constexpr GLuint attrib_sizes[] = { 2 };
        constexpr const char *attrib_names[] = { "position" };
        static_assert(std::size(attrib_names) == Buffer::BUFFER_COUNT);
        for (std::size_t i = 0; i < std::size(attrib_names); ++i) {
            auto &attrib = m_attribs[i];
            attrib = glGetAttribLocation(prog_shdr, attrib_names[i]);
            glBindBuffer(GL_ARRAY_BUFFER, m_buffers[i]);
            glEnableVertexAttribArray(attrib);
            glVertexAttribPointer(attrib, attrib_sizes[i], GL_FLOAT, GL_FALSE, 0, 0);
        }

        constexpr const char *uniform_names[] = { "translate", "angle", "mvp" };
        static_assert(std::size(uniform_names) == Uniform::UNIFORM_COUNT);
        for (std::size_t i = 0; i < std::size(uniform_names); ++i) {
            m_uniforms[i] = glGetUniformLocation(prog_shdr, uniform_names[i]);
        }

        float r = static_cast<float>(win.width()) / win.height();
        mat4x4 mvp, s;
        mat4x4_identity(s);
        mat4x4_scale_aniso(s, s, WORLD_SCALE, WORLD_SCALE, WORLD_SCALE);
        mat4x4_ortho(mvp, -r, r, -1, 1, 0, 1);
        mat4x4_mul(mvp, mvp, s);
        glUniformMatrix4fv(m_uniforms[Uniform::MVP], 1, GL_FALSE, reinterpret_cast<GLfloat *>(mvp));
    }

    void Graphics::draw(const Entity &ent) {
        auto &shape = ent.shape();
        std::vector<float> vertices{};
        vertices.reserve(shape.m_count * 2);
        for (std::size_t i = 0; i < shape.m_count; ++i) {
            auto &vertex = shape.m_vertices[i];
            vertices.push_back(vertex.x);
            vertices.push_back(vertex.y);
        }
        glBindBuffer(GL_ARRAY_BUFFER, m_buffers[Buffer::POSITION]);
        glBufferData(GL_ARRAY_BUFFER, byte_size(vertices), vertices.data(), GL_STREAM_DRAW);

        auto &pos = ent.body()->GetPosition();
        glUniform2f(m_uniforms[Uniform::TRANSLATE], pos.x, pos.y);
        glUniform1f(m_uniforms[Uniform::ANGLE], ent.body()->GetAngle());

        glDrawArrays(GL_TRIANGLE_FAN, 0, shape.m_count);
    }

}
