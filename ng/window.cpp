#include "window.h"
#include <iostream>

namespace ng {

    Window::Window(std::string name, int w, int h) {
        auto err_callback = [](int err, const char *desc) {
            std::cout << "GLFW Error [" << err << "]: " << desc << std::endl;
        };
        glfwSetErrorCallback(err_callback);

        glfwInit();

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
