#pragma once

#include "gl.h"

namespace ng {

    class Window {
        GLFWwindow *m_win;

        int m_win_w;
        int m_win_h;

    public:
        Window();
        ~Window();

        bool poll();

        inline GLFWwindow *get() { return m_win; }

        inline int width()  { return m_win_w; }
        inline int height() { return m_win_h; }
    };

}