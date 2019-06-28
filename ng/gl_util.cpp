#include "gl_util.h"
#include <iostream>
#include <vector>

namespace gl_util {

    bool check_shader_compile(GLuint shader) {
        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            GLint size = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
            std::vector<GLchar> error_log(size + 1);
            glGetShaderInfoLog(shader, size, &size, &error_log[0]);
            glDeleteShader(shader);
            std::cout << error_log.data() << std::endl;
        }
        return success == GL_TRUE;
    }

    bool check_program_link(GLuint program) {
        GLint success = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (success == GL_FALSE) {
            GLint size = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
            std::vector<GLchar> error_log(size + 1);
            glGetProgramInfoLog(program, size, &size, &error_log[0]);
            glDeleteProgram(program);
            std::cout << error_log.data() << std::endl;
        }
        return success == GL_TRUE;
    }

}
