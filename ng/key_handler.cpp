#include "key_handler.h"
#include "assert.h"

inline void default_handler(GLFWwindow *, int, int) {}

namespace ng {

    KeyHandler::KeyHandler() {
        m_delegates.fill(&default_handler);
    }

    void KeyHandler::callback(GLFWwindow *win, int key, int, int action, int mods) {
        ng_assert(0 <= key < NUM_KEYS);
        static_assert(GLFW_RELEASE == 0);
        static_assert(GLFW_PRESS == 1);
        auto& kh = get();
        bool &val = kh.m_key_map[key];
        val = action <= 1 ? static_cast<bool>(action) : val;
        kh.m_delegates[key](win, action, mods);
    }

    void KeyHandler::remove_delegate(int key) {
        m_delegates[key] = &default_handler;
    }

}
