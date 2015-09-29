#pragma once

#include <gpc/gl/wrappers.hpp>

#include "triangle_strip.hpp"

namespace gpc {

    namespace gl {
    
        struct TexturedRectangleVertexData {
            FloatVec4 coordinates;
            FloatVec4 texture_coords;
        };

        // TODO: provide specializations of this template to work with GLint as well as GLfloat

        extern const VertexAttribute _texturedRectangleAttributes[2];

        class TexturedRectangle : public TriangleStrip<TexturedRectangleVertexData, _texturedRectangleAttributes, 2> {
        public:

            TexturedRectangle(): texture(0) {}

            void allocResources() {

                TriangleStrip::allocResources();
                EXEC_GL(glGenTextures, 1, &texture);
            }

            void freeResources() {

                EXEC_GL(glDeleteTextures, 1, &texture); 
                texture = 0;
                TriangleStrip::freeResources();
            }

            /** Uploads 2D vertices with both pixel and texel coordinates.
                TODO: optional parameters to separately define the texture corners.
             */
            void uploadVertices(GLint width, GLint height) {
                
                TexturedRectangleVertexData vertices[4] = {
                    { { (GLfloat)     0, (GLfloat)      0, 0, 1}, { (GLfloat)     0, (GLfloat)      0, 0, 1} },
                    { { (GLfloat) width, (GLfloat)      0, 0, 1}, { (GLfloat) width, (GLfloat)      0, 0, 1} },
                    { { (GLfloat)     0, (GLfloat) height, 0, 1}, { (GLfloat)     0, (GLfloat) height, 0, 1} },
                    { { (GLfloat) width, (GLfloat) height, 0, 1}, { (GLfloat) width, (GLfloat) height, 0, 1} }
                };

                TriangleStrip::uploadData(4, vertices);
            }

            void uploadPicture(int width, int height, const void *pixels, 
                int internal_format = (int) GL_RGBA, GLenum format = GL_RGBA
                ) 
            {
                bindTexture();

                EXEC_GL(glTexImage2D, GL_TEXTURE_RECTANGLE, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
            }

            void draw() {

                bindTexture();

                TriangleStrip::draw(4);
            }

            void drawBlank() {

                EXEC_GL(glBindTexture, GL_TEXTURE_RECTANGLE, 0);

                TriangleStrip::draw(4);
            }

            void unbindAll() {

                EXEC_GL(glBindTexture, GL_TEXTURE_RECTANGLE, 0);
            }

        private:

            void bindTexture() { EXEC_GL(glBindTexture, GL_TEXTURE_RECTANGLE, texture); }

            GLuint texture;
        };

    } // ns gl

} // ns gpc
