#include "assert.h"
#include "mouse_handler.h"

namespace ng {

    MouseHandler *MouseHandler::s_instance = nullptr;

    void MouseHandler::callback(GLFWwindow *win, int button, int action, int mods) {
        ng_assert(0 <= button && button < NUM_BUTTONS);
        ng_assert(s_instance != nullptr);

        MouseHandler &mh = *s_instance;
        mh.m_delegates[button](win, action, mods);
    }

    MouseHandler::MouseHandler(GLFWwindow *win) {
        m_delegates.fill([](GLFWwindow *, int, int) { });

        ng_assert(s_instance == nullptr);
        s_instance = this;
        glfwSetMouseButtonCallback(win, &MouseHandler::callback);
    }

}
