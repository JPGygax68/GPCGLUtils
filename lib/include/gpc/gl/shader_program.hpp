#pragma once

#include <string>

#include <gpc/gl/wrappers.hpp>

namespace gpc {

    namespace gl {

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
        compileShader(GLuint shader, const std::string &source, const std::string &defines = "") -> std::string
        {
            // NOTE: this method of adding #define's to a shader violates the GLSL specification that says that
            //  the first non-blank, non-comment statement must be #version
            std::vector<const char *> sources;
            std::vector<GLint> lengths;
            if (!defines.empty()) {
                sources.push_back(defines.c_str()); lengths.push_back(defines.size());
                sources.push_back("\n#line 1\n"); lengths.push_back(1);
            }
            sources.push_back(source.data());
            lengths.push_back(source.size());
            EXEC_GL(glShaderSource, shader, sources.size(), &sources[0], &lengths[0]);
            EXEC_GL(glCompileShader, shader);
            GLint compiled;
            EXEC_GL(glGetShaderiv, shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled) throw std::runtime_error(std::string("Failed to compile shader:\n") + gpc::gl::getShaderCompilationLog(shader));
            return getShaderCompilationLog(shader);
        }

        inline GLuint buildShaderProgram(const std::string &vertex_code, const std::string &fragment_code) {

            GLuint vertex_shader = CALL_GL(glCreateShader, GL_VERTEX_SHADER);
            GLuint fragment_shader = CALL_GL(glCreateShader, GL_FRAGMENT_SHADER);

            gpc::gl::compileShader(vertex_shader, vertex_code);
            gpc::gl::compileShader(fragment_shader, fragment_code);

            return buildShaderProgram(vertex_shader, fragment_shader);
        }

        inline GLuint buildShaderProgram(GLuint vertex_shader, GLuint fragment_shader) {

            GLuint program = CALL_GL(glCreateProgram);

            EXEC_GL(glAttachShader, program, vertex_shader);
            EXEC_GL(glAttachShader, program, fragment_shader);

            EXEC_GL(glLinkProgram, program);

            return program;
        }

    } // ns gl

} // ns gpc
