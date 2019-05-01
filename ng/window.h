#pragma once

#include "gl.h"
#include <string>

namespace ng {

    class Window {
        GLFWwindow *m_win;

        int m_win_w;
        int m_win_h;

    public:
        Window(std::string name, int w, int h);
        ~Window();

        bool poll();

        inline GLFWwindow *get() { return m_win; }

        inline int width()  const { return m_win_w; }
        inline int height() const { return m_win_h; }
    };

}
