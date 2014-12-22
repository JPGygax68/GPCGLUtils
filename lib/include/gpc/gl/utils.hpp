#pragma once

#include <cassert>
#include <gpc/gl/wrappers.hpp>

namespace gpc {

    namespace gl {
    
#ifdef _DEBUG
        inline void checkUniformLocation(const char *name, GLuint location) {
            GLint program = 0;
            EXEC_GL(glGetIntegerv, GL_CURRENT_PROGRAM, &program);
            assert(program > 0);
            GLuint loc = CALL_GL(glGetUniformLocation, program, name);
            assert(loc == location);
        }
#else
        inline void checkUniformLocation(GLuint program, const char *name, GLuint index) {}
#endif

        inline void setUniform(const char *name, GLuint index, GLint value) {
            checkUniformLocation(name, index);
            EXEC_GL(glUniform1i, index, value);
        }

        template <int Count>
        inline void setUniform(const char *name, GLuint index, const GLfloat *values) {
            checkUniformLocation(name, index);
            EXEC_GL(glUniform4fv, index, 1, values);
        }

        inline std::string getShaderCompilationLog(GLuint shader) {
            GLint log_size = 0;
            EXEC_GL(glGetShaderiv, shader, GL_INFO_LOG_LENGTH, &log_size);
            std::string log(log_size, 0);
            GLsizei real_size = 0;
            EXEC_GL(glGetShaderInfoLog, shader, log.size(), &real_size, &log[0]);
            return log;
        }

    } // ns gl
    
} // ns gpc
