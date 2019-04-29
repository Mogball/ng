#include "key_handler.h"
#include "window.h"
#include <linmath.h>
#include <iostream>

static constexpr auto s_vert_code = R"glsl(
    #version 150 core

    in vec2 position;

    uniform mat4 mvp;
    uniform vec2 pos;

    void main() {
        gl_Position = mvp * vec4(pos + position, 0.0, 1.0);
    }
)glsl";

static constexpr auto s_frag_code = R"glsl(
    #version 150 core

    void main() {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)glsl";

static constexpr float vertices[8] = {
    -0.5, -0.5,
     0.5, -0.5,
     0.5,  0.5,
    -0.5,  0.5,
};

int main() {
    ng::Window window;
    ng::KeyHandler handler{ window.get() };
    handler.set_delegate(GLFW_KEY_E, [](GLFWwindow *, int action, int) {
        if (action >= 2) { return; }
        std::cout << (action ? "Pressed" : "Released") << std::endl;
    });
    handler.set_delegate(GLFW_KEY_ESCAPE, [](GLFWwindow *win, int action, int) {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
    });


    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
    glEnableVertexAttribArray(attrib_pos);
    glVertexAttribPointer(attrib_pos, 2, GL_FLOAT, GL_FALSE, 0, 0);

    GLint uniform_pos = glGetUniformLocation(program, "pos");
    float pos[] = { 0.2, 0.2 };
    glUniform2fv(uniform_pos, 1, pos);

    float r = static_cast<float>(window.width()) / window.height();

    mat4x4 proj, model, mvp;
    mat4x4_ortho(proj, -r, r, -1, 1, 0, 1);
    mat4x4_identity(model);
    mat4x4_mul(mvp, proj, model);
    GLint uniform_mvp = glGetUniformLocation(program, "mvp");
    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, reinterpret_cast<GLfloat *>(mvp));

    while (window.poll()) {
        glViewport(0, 0, window.width(), window.height());
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    return EXIT_SUCCESS;
}
