#include "assert.h"
#include "key_handler.h"

namespace ng {

    KeyHandler *KeyHandler::s_instance = nullptr;

    void KeyHandler::callback(GLFWwindow *win, int key, int, int action, int mods) {
        ng_assert(0 <= key && key < NUM_KEYS);
        ng_assert(s_instance != nullptr);
        static_assert(GLFW_RELEASE == 0);
        static_assert(GLFW_PRESS == 1);

        KeyHandler &kh = *s_instance;
        auto &val = kh.m_key_map[key];
        val = action <= 1 ? static_cast<bool>(action) : val;

        kh.m_delegates[key](win, action, mods);
    }

    KeyHandler::KeyHandler(GLFWwindow *win) {
        m_delegates.fill([](GLFWwindow *, int, int) { });

        ng_assert(s_instance == nullptr);
        s_instance = this;
        glfwSetKeyCallback(win, &KeyHandler::callback);
    }

}
