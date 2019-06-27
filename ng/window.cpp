#include "window.h"
#include <iostream>

namespace ng {

    Window::Window(std::string name, int w, int h) {
        auto err_callback = [](int err, const char *desc) {
            std::cout << "GLFW Error [" << err << "]: " << desc << std::endl;
        };

        glfwInit();
        glfwSetErrorCallback(err_callback);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        m_win = glfwCreateWindow(w, h, name.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(m_win);
        gladLoadGL(glfwGetProcAddress);
        glfwSwapInterval(1);

        glfwGetFramebufferSize(m_win, &m_win_w, &m_win_h);
    }

    Window::~Window() {
        glfwDestroyWindow(m_win);
        glfwTerminate();
    }

    bool Window::poll() {
        glfwSwapBuffers(m_win);
        glfwPollEvents();
        return !glfwWindowShouldClose(m_win);
    }

}
