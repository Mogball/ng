#pragma once

#include "gl.h"
#include <functional>

namespace ng {

    class MouseHandler {
    public:
        typedef std::function<void(GLFWwindow *, int, int)> Delegate;

    private:
        static constexpr auto NUM_BUTTONS = GLFW_MOUSE_BUTTON_LAST + 1;
        static void callback(GLFWwindow *win, int button, int action, int mods);
        static MouseHandler *s_instance;

        std::array<Delegate, NUM_BUTTONS> m_delegates{};

    public:
        MouseHandler(GLFWwindow *win);

        inline void set_delegate(int button, Delegate del) {
            m_delegates[button] = del;
        }

        inline void remove_delegate(int button) {
            m_delegates[button] = [](GLFWwindow *, int, int) { };
        }
    };

}
