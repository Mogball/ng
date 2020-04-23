#include "gl_util.h"
#include <iostream>
#include <vector>
#include <cstdlib>

static std::string gl_err_to_string(GLenum err) {
    switch (err) {
    case GL_NO_ERROR:
        return "GL_NO_ERROR";
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
    case GL_STACK_UNDERFLOW:
        return "GL_STACK_UNDERFLOW";
    case GL_STACK_OVERFLOW:
        return "GL_STACK_OVERFLOW";
    default:
        return "UNKNOWN_ERROR";
    }
}

namespace gl_util {

    bool check_shader_compile(GLuint shader) {
        GLint success = 0;
        CHECK_ERR(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
        if (success == GL_FALSE) {
            GLint size = 0;
            CHECK_ERR(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size));
            std::vector<GLchar> error_log(size + 1);
            CHECK_ERR(glGetShaderInfoLog(shader, size, &size, &error_log[0]));
            CHECK_ERR(glDeleteShader(shader));
            std::cout << error_log.data() << std::endl;
        }
        return success == GL_TRUE;
    }

    bool check_program_link(GLuint program) {
        GLint success = 0;
        CHECK_ERR(glGetProgramiv(program, GL_LINK_STATUS, &success));
        if (success == GL_FALSE) {
            GLint size = 0;
            CHECK_ERR(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size));
            std::vector<GLchar> error_log(size + 1);
            CHECK_ERR(glGetProgramInfoLog(program, size, &size, &error_log[0]));
            CHECK_ERR(glDeleteProgram(program));
            std::cout << error_log.data() << std::endl;
        }
        return success == GL_TRUE;
    }

    void check_err(int line, std::string file, std::string func, std::string call) {
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cout << "OpenGL ERROR: " << err << " -> " << gl_err_to_string(err) << std::endl;
            std::cout << file << ":" << line << " -> " << func << std::endl;
            std::cout << call << std::endl;
            exit(-1);
        }
    }

}
