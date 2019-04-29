#pragma once

#include "gl.h"
#include <array>
#include <functional>

namespace ng {

    class KeyHandler {
    public:
        typedef std::function<void(GLFWwindow *, int, int)> Delegate;

    private:
        static constexpr auto NUM_KEYS = GLFW_KEY_LAST + 1;
        static void callback(GLFWwindow *win, int key, int code, int action, int mods);
        static KeyHandler *s_instance;

        std::array<bool, NUM_KEYS> m_key_map{};
        std::array<Delegate, NUM_KEYS> m_delegates{};

    public:
        KeyHandler(GLFWwindow *win);

        inline bool pressed(int key) {
            return m_key_map[key];
        }

        inline void set_delegate(int key, Delegate del) {
            m_delegates[key] = del;
        }

        inline void remove_delegate(int key) {
            m_delegates[key] = [](GLFWwindow *, int, int) {};
        }
    };

}
