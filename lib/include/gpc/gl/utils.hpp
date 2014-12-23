#pragma once

#include <cassert>
#include <vector>
#include <gpc/gl/wrappers.hpp>

namespace gpc {

    namespace gl {
    
#ifdef _DEBUG
        inline void checkUniformLocation(const char *name, GLuint location) 
        {
            GLint program = 0;
            EXEC_GL(glGetIntegerv, GL_CURRENT_PROGRAM, &program);
            assert(program > 0);
            GLuint loc = CALL_GL(glGetUniformLocation, program, name);
            assert(loc == location);
        }
#else
        inline void checkUniformLocation(GLuint program, const char *name, GLuint index) {}
#endif

        inline void setUniform(const char *name, GLuint index, GLint value)
        {
            checkUniformLocation(name, index);
            EXEC_GL(glUniform1i, index, value);
        }

        template <int Count>
        inline void 
        setUniform(const char *name, GLuint index, const GLfloat *values) 
        {
            checkUniformLocation(name, index);
            EXEC_GL(glUniform4fv, index, 1, values);
        }

        inline auto
        getShaderCompilationLog(GLuint shader) -> std::string
        {
            GLint log_size = 0;
            EXEC_GL(glGetShaderiv, shader, GL_INFO_LOG_LENGTH, &log_size);
            std::string log(log_size, 0);
            GLsizei real_size = 0;
            EXEC_GL(glGetShaderInfoLog, shader, log.size(), &real_size, &log[0]);
            log.resize(real_size);
            return log;
        }

        inline auto
        compileShader(GLuint shader, const std::string source, const std::string defines = "") -> std::string
        {
            // NOTE: this method of adding #define's to a shader violates the GLSL specification that says that
            //  the first non-blank, non-comment statement must be #version
            std::vector<const char *> sources;
            std::vector<GLint> lengths;
            if (!defines.empty()) { 
                sources.push_back(defines.c_str()); lengths.push_back(defines.size()); 
                sources.push_back("\n#line 1\n"); lengths.push_back(1);
            }
            sources.push_back(source.c_str());
            lengths.push_back(source.size());
            EXEC_GL(glShaderSource, shader, sources.size(), &sources[0], &lengths[0]);
            EXEC_GL(glCompileShader, shader);
            GLint compiled;
            EXEC_GL(glGetShaderiv, shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled) throw std::runtime_error(std::string("Failed to compile shader:\n") + gpc::gl::getShaderCompilationLog(shader));
            return getShaderCompilationLog(shader);
        }

    } // ns gl
    
} // ns gpc
