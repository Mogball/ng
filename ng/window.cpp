#include "window.h"
#include <iostream>

static constexpr auto WIDTH = 1920;
static constexpr auto HEIGHT = 1080;
static constexpr auto NAME = "Memes";

namespace ng {

    Window::Window() {
        auto err_callback = [](int err, const char *desc) {
            std::cout << "GLFW Error [" << err << "]: " << desc << std::endl;
        };
        glfwSetErrorCallback(err_callback);

        glfwInit();

        m_win = glfwCreateWindow(WIDTH, HEIGHT, NAME, nullptr, nullptr);

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
