#include "entity.h"
#include "key_handler.h"
#include "graphics.h"
#include "window.h"
#include <linmath.h>
#include <iostream>

static constexpr auto s_vert_code = R"glsl(
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
        gl_Position = mvp * vec4(translate + rot(angle) * position * ratio(scale), 0.0, 1.0);
    }
)glsl";

static constexpr auto s_frag_code = R"glsl(
    #version 150 core

    void main() {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)glsl";

static constexpr float vertices[8] = {
    -1, -1,
    1, -1,
    1, 1,
    -1, 1,
};

static constexpr float translate[4] = {
    0.2, 0.2,
    -0.5, 0,
};

static constexpr float angle[2] = {
    0.1, 0.2,
};

static constexpr float scale[2] = {
    0.5, 0.3,
};

using namespace ng;

int main() {
    Window window;
    KeyHandler handler{ window.get() };
    handler.set_delegate(GLFW_KEY_E, [](GLFWwindow *, int action, int) {
        if (action >= 2) { return; }
        std::cout << (action ? "Pressed" : "Released") << std::endl;
    });
    handler.set_delegate(GLFW_KEY_ESCAPE, [](GLFWwindow *win, int action, int) {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
    });

    Graphics graphics{ window };
    return 0;


    GLuint buffer_pos;
    glGenBuffers(1, &buffer_pos);
    GLuint buffer_trans;
    glGenBuffers(1, &buffer_trans);
    GLuint buffer_angle;
    glGenBuffers(1, &buffer_angle);
    GLuint buffer_scale;
    glGenBuffers(1, &buffer_scale);

    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, &s_vert_code, nullptr);
    glCompileShader(vert_shader);

    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &s_frag_code, nullptr);
    glCompileShader(frag_shader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);
    glLinkProgram(program);
    glUseProgram(program);

    GLint attrib_pos = glGetAttribLocation(program, "position");
    glBindBuffer(GL_ARRAY_BUFFER, buffer_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attrib_pos);
    glVertexAttribPointer(attrib_pos, 2, GL_FLOAT, GL_FALSE, 0, 0);

    GLint attrib_trans = glGetAttribLocation(program, "translate");
    glBindBuffer(GL_ARRAY_BUFFER, buffer_trans);
    glBufferData(GL_ARRAY_BUFFER, sizeof(translate), translate, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attrib_trans);
    glVertexAttribPointer(attrib_trans, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribDivisor(attrib_trans, 1);

    GLint attrib_angle = glGetAttribLocation(program, "angle");
    glBindBuffer(GL_ARRAY_BUFFER, buffer_angle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(angle), angle, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attrib_angle);
    glVertexAttribPointer(attrib_angle, 1, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribDivisor(attrib_angle, 1);

    GLint attrib_scale = glGetAttribLocation(program, "scale");
    glBindBuffer(GL_ARRAY_BUFFER, buffer_scale);
    glBufferData(GL_ARRAY_BUFFER, sizeof(scale), scale, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attrib_scale);
    glVertexAttribPointer(attrib_scale, 1, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribDivisor(attrib_scale, 1);

    float r = static_cast<float>(window.width()) / window.height();

    mat4x4 proj, model, mvp;
    mat4x4_ortho(proj, -r, r, -1, 1, 0, 1);
    mat4x4_identity(model);
    mat4x4_mul(mvp, proj, model);
    GLint uniform_mvp = glGetUniformLocation(program, "mvp");
    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, reinterpret_cast<GLfloat *>(mvp));

    glViewport(0, 0, window.width(), window.height());
    while (window.poll()) {
        glClear(GL_COLOR_BUFFER_BIT);

        unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
        //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glDrawElementsInstancedBaseVertex(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, reinterpret_cast<GLvoid *>(indices), 2, 0);
    }

    return EXIT_SUCCESS;
}
