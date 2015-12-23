#pragma once

#include <cassert>

#include <gpc/gl/wrappers.hpp>

#include "triangle_strip.hpp"

namespace gpc {

    namespace gl {
    
        struct DefaultTexturedRectangleVertexData {
            FloatVec4 coordinates;
            FloatVec2 texture_coords;
        };

        struct FPTexturedRectangleVertexData {
            FloatVec4 coordinates;
            FloatVec4 texture_coords;
        };

        // TODO: provide specializations of this template to work with GLint as well as GLfloat

        extern const VertexAttribute _nvDefaultTexRectAttribs[2];
        extern const VertexAttribute _nvFPTexRectAttribs[2];

        template <
            GLenum TextureType = GL_TEXTURE_RECTANGLE, 
            bool AllocTexture = true,
            typename VertexStruct = DefaultTexturedRectangleVertexData,
            const VertexAttribute *AttribList = _nvDefaultTexRectAttribs
        >
        class TexturedRectangle : public TriangleStrip<VertexStruct, AttribList, 2> {
        public:

            TexturedRectangle() {}

            void allocResources() {

                TriangleStrip::allocResources();
                tex_mgr.genTexture();
            }

            void freeResources() {

                tex_mgr.deleteTextures();
                TriangleStrip::freeResources();
            }

            /** Uploads 2D vertices with both pixel and texel coordinates.
                TODO: optional parameters to separately define the texture corners.
             */
            void uploadVertices(GLint width, GLint height, GLint x = 0, GLint y = 0) {
                
                TexCoordSet tex_coords;
                TexCoordGen<TextureType>::get_coords(width, height, tex_coords);

                // TODO: implement via specialization
                VertexStruct vertices[4] = {
                    { { (GLfloat) x        , (GLfloat) y         , 0, 1}, { tex_coords[0][0], tex_coords[0][1]} },
                    { { (GLfloat) x + width, (GLfloat) y         , 0, 1}, { tex_coords[1][0], tex_coords[1][1]} },
                    { { (GLfloat) x        , (GLfloat) y + height, 0, 1}, { tex_coords[2][0], tex_coords[2][1]} },
                    { { (GLfloat) x + width, (GLfloat) y + height, 0, 1}, { tex_coords[3][0], tex_coords[3][1]} }
                };

                TriangleStrip::uploadData(4, vertices);
            }

            void uploadPicture(int width, int height, const void *pixels, 
                int internal_format = (int) GL_RGBA, GLenum format = GL_RGBA
                ) 
            {
                tex_mgr.checkOwningTexture();

                bindTexture();

                EXEC_GL(glTexImage2D, TextureType, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
            }

            void draw() {

                tex_mgr.bindTexture();

                TriangleStrip::draw(4);

                unbindAll();
            }

            void drawBlank() {

                EXEC_GL(glBindTexture, TextureType, 0);

                TriangleStrip::draw(4);
            }

            void unbindAll() {

                EXEC_GL(glBindTexture, TextureType, 0);
            }

        private:

            typedef FloatVec2 TexCoordSet[4];

            template <GLenum TextureType>
            struct TexCoordGen {
            };
            
            template <>
            struct TexCoordGen<GL_TEXTURE_2D> {
                static void get_coords(GLint width, GLint height, TexCoordSet &coords)
                {
                    using namespace std;

                    static const TexCoordSet values = { 
                        {0, 0},
                        {1, 0},
                        {0, 1},
                        {1, 1}
                    };

                    for (int i = 0; i < 4; i ++) copy(begin(values[i]), end(values[i]), begin(coords[i]));
                }
            };

            template <>
            struct TexCoordGen<GL_TEXTURE_RECTANGLE> {
                static void get_coords(GLint width, GLint height, TexCoordSet &coords)
                {
                    TexCoordSet values = { 
                        { (GLfloat)     0, (GLfloat)      0},
                        { (GLfloat) width, (GLfloat)      0},
                        { (GLfloat)     0, (GLfloat) height},
                        { (GLfloat) width, (GLfloat) height}
                    };

                    for (int i = 0; i < 4; i ++) copy(begin(values[i]), end(values[i]), begin(coords[i]));
                }
            };

            template <bool OwnTexture>
            struct TexManager {};

            template <> struct TexManager<true> {
                auto genTexture() -> GLuint {
                    EXEC_GL(glGenTextures, 1, &texture);
                    return texture;
                }

                void freeTexture() {
                    EXEC_GL(glDeleteTextures, 1, &texture);
                    texture = 0;
                }

                void bindTexture() { EXEC_GL(glBindTexture, TextureType, texture); }

                void checkOwningTexture() {}

                GLuint texture;
            };

            template <> struct TexManager<false> {
                auto genTexture() -> GLuint { return 0; }
                void freeTexture() {}
                void bindTexture() {}
                void checkOwningTexture() { assert(false); }
            };

            TexManager<AllocTexture> tex_mgr;
        };

    } // ns gl

} // ns gpc
