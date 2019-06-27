#pragma once

#include "gl.h"

namespace gl_util {

    bool check_shader_compile(GLuint shader);
    bool check_program_link(GLuint program);

}
