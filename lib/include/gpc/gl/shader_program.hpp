#pragma once

#include <string>
#include <vector>


// DECLARATIONS --------------------------------------------

namespace gpc {

    namespace gl {

        auto getShaderCompilationLog(GLuint shader) -> std::string;
            
        auto insertLinesIntoShaderSource(const std::string &source, const std::string &lines) -> std::string;

        auto compileShader(GLuint shader, const std::string &source, const std::string &defines = "") -> std::string;

        GLuint buildShaderProgram(const std::string &vertex_code, const std::string &fragment_code);

        GLuint buildShaderProgram(GLuint vertex_shader, GLuint fragment_shader);

        auto getProgramInfoLog(GLuint progr) -> std::string;

    } // ns gl

} // ns gpc


// Implementation -------------------------------------------

namespace gpc {

    namespace gl {

        inline auto
            getShaderCompilationLog(GLuint shader) -> std::string
        {
            GLint log_size = 0;
            GL(GetShaderiv, shader, GL_INFO_LOG_LENGTH, &log_size);
            std::string log(log_size, 0);
            GLsizei real_size = 0;
            GL(GetShaderInfoLog, shader, log.size(), &real_size, &log[0]);
            log.resize(real_size);
            return log;
        }

        inline auto
            compileShader(GLuint shader, const std::string &source, const std::string &defines) -> std::string
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
            GL(ShaderSource, shader, sources.size(), &sources[0], &lengths[0]);
            GL(CompileShader, shader);
            GLint compiled;
            GL(GetShaderiv, shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled) throw std::runtime_error(std::string("Failed to compile shader:\n") + gpc::gl::getShaderCompilationLog(shader));
            return getShaderCompilationLog(shader);
        }

        inline GLuint buildShaderProgram(const std::string &vertex_code, const std::string &fragment_code) {

            GLuint vertex_shader = GL(CreateShader, GL_VERTEX_SHADER);
            GLuint fragment_shader = GL(CreateShader, GL_FRAGMENT_SHADER);

            gpc::gl::compileShader(vertex_shader, vertex_code);
            gpc::gl::compileShader(fragment_shader, fragment_code);

            return buildShaderProgram(vertex_shader, fragment_shader);
        }

        inline GLuint buildShaderProgram(GLuint vertex_shader, GLuint fragment_shader) {

            GLuint program = GL(CreateProgram);

            GL(AttachShader, program, vertex_shader);
            GL(AttachShader, program, fragment_shader);

            GL(LinkProgram, program);

            return program;
        }

        inline auto getProgramInfoLog(GLuint prog) -> std::string
        {
            char buffer[30*120]; 

            GLsizei size;
            GL(GetProgramInfoLog, prog, sizeof(buffer), &size, buffer);

            return std::string(buffer, size);
        }

    } // ns gl

} // ns gpc
