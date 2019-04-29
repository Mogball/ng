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

        std::array<bool, NUM_KEYS> m_key_map{};
        std::array<Delegate, NUM_KEYS> m_delegates{};

        KeyHandler();

    public:
        static inline KeyHandler &get() {
            static KeyHandler instance;
            return instance;
        }

        inline bool pressed(int key) {
            return m_key_map[key];
        }

        inline void register_handler(GLFWwindow *win) {
            glfwSetKeyCallback(win, &KeyHandler::callback);
        }

        inline void set_delegate(int key, Delegate del) {
            m_delegates[key] = del;
        }

        void remove_delegate(int key);
    };

}
