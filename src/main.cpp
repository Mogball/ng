#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

static constexpr auto s_vert_code = R"glsl(
    #version 150 core

    in vec2 position;

    void main() {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";

static constexpr auto s_frag_code = R"glsl(
    #version 150 core

    void main() {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)glsl";

static void S_error_callback(int err, const char *desc) {
    std::cout << "Error [" << err << "]: " << desc << std::endl;
}

static void S_key_callback(GLFWwindow *win, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS) {
        return;
    }

    switch (key) {
    case GLFW_KEY_SPACE:
        std::cout << "Space Bar!" << std::endl;
        break;
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(win, GLFW_TRUE);
        break;
    }
}

static constexpr float vertices[8] = {
    -0.5, -0.5,
     0.5, -0.5,
     0.5,  0.5,
    -0.5,  0.5,
};

int main() {
    std::cout << "Hello world!" << std::endl;

    glfwSetErrorCallback(S_error_callback);
    if (!glfwInit()) {
        std::cout << "Failed: glfwInit()" << std::endl;
        return EXIT_FAILURE;
    }

    GLFWwindow *win = glfwCreateWindow(1920, 1080, "Memes", nullptr, nullptr);
    if (!win) {
        std::cout << "Failed: glfwCreateWindow()" << std::endl;
        return EXIT_FAILURE;
    }

    glfwSetKeyCallback(win, S_key_callback);
    glfwMakeContextCurrent(win);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

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

    GLuint attrib_pos = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(attrib_pos);
    glVertexAttribPointer(attrib_pos, 2, GL_FLOAT, GL_FALSE, 0, 0);

    int w, h;
    glfwGetFramebufferSize(win, &w, &h);

    while (!glfwWindowShouldClose(win)) {
        glViewport(0, 0, w, h);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwDestroyWindow(win);
    glfwTerminate();
    return EXIT_SUCCESS;
}
