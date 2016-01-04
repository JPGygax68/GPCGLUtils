#pragma once

#include <memory>

#include <gpc/gl/wrappers.hpp>

#include "utils.hpp" // TODO: replace with "types.hpp" when that is done

namespace gpc {
    
    namespace gl {
        
        struct VertexAttribute {
            GLenum type;
            GLint  count;
            GLint index;
            // TODO: "normalized" field ?
        };

        // TODO: rename, since it can now contain multiple strips ?

        template <class VertexData = FloatVec3, const VertexAttribute *AttribList = nullptr, unsigned int AttribCount = 0>
        class TriangleStrip {
            
        public:

            typedef typename VertexData vertex_t;

            typedef GLushort index_t;

            TriangleStrip(): vertex_buffer(0), index_buffer(0) {}

            void allocResources() {
                
                GL(GenBuffers, 1, &vertex_buffer);
                GL(GenBuffers, 1, &index_buffer);
            }
            
            void freeResources() {

                GL(DeleteBuffers, 1, &vertex_buffer);
                GL(DeleteBuffers, 1, &index_buffer);
            }
            
            void uploadData(size_t vertex_count, const vertex_t *vertices) {

                std::unique_ptr<index_t> indices( new index_t [vertex_count] );
                for (GLushort i = 0; i < vertex_count; i ++) indices.get()[i] = i;

                uploadData(vertex_count, vertices, vertex_count, indices.get());
            }

            void uploadData(size_t vertex_count, const vertex_t *vertices, size_t index_count, const index_t *indices) {

                GL(BindBuffer, GL_ARRAY_BUFFER, vertex_buffer);
                GL(BufferData, GL_ARRAY_BUFFER, vertex_count * sizeof(vertex_t), vertices, GL_STATIC_DRAW);
                GL(BindBuffer, GL_ARRAY_BUFFER, 0);

                GL(BindBuffer, GL_ELEMENT_ARRAY_BUFFER, index_buffer);
                GL(BufferData, GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(index_t), indices, GL_STATIC_DRAW);
                GL(BindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);
            }

            void draw(size_t index_count) {

                draw(0, index_count);
            }
            
            void draw(size_t index_base, size_t index_count) {

                GL(BindBuffer, GL_ARRAY_BUFFER, vertex_buffer);

                if (AttribList) {
                    size_t offset = 0;
                    const VertexAttribute *attr = AttribList;
                    for (GLuint i = 0; i < AttribCount; i++, attr++) {
                        GL(EnableVertexAttribArray, attr->index);
                        GL(VertexAttribPointer, attr->index, attr->count, attr->type, GL_FALSE, sizeof(VertexData), (const GLvoid *)offset);
                        offset += attr->count * attributeSize(attr->type);
                    }
                }
                else {
                    GL(EnableClientState, (GL_VERTEX_ARRAY));
                    GL(VertexPointer, 3, GL_FLOAT, sizeof(vertex_t), (void*)0); // TODO: HACK! REMOVE! REMOVE!
                    // TODO: use glTexCoordPointer() as well when necessary
                }
                GL(BindBuffer, GL_ELEMENT_ARRAY_BUFFER, index_buffer);

                GL(DrawElements, GL_TRIANGLE_STRIP, index_count, GL_UNSIGNED_SHORT, (void*)(index_base*sizeof(GLushort)));

                GL(BindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);
                GL(BindBuffer, GL_ARRAY_BUFFER, 0);
                if (AttribList) {
                    const VertexAttribute *attr = AttribList;
                    for (GLuint i = 0; i < AttribCount; i++, attr++) {
                        GL(DisableVertexAttribArray, attr->index);
                    }
                }
                else
                {
                    GL(DisableClientState, (GL_VERTEX_ARRAY));
                }
            }

        private:

            // TODO: make this constexpr

            static size_t attributeSize(GLenum type) {
                switch(type) {
                case GL_INT: return sizeof(GLint);
                case GL_UNSIGNED_INT: return sizeof(GLuint);
                case GL_FLOAT: return sizeof(GLfloat);
                case GL_DOUBLE: return sizeof(GLdouble);
                // TODO: support all types supported by glVertexAttribPointer()
                default: assert(false); return 0;
                }
            }

            GLuint vertex_buffer;
            GLuint index_buffer;
        };
        

        // Triangle strip with only x, y GLfloat coordinates
        typedef TriangleStrip<FloatVec2> TriangleStrip2D;

        // Triangle strip with x, y, z GLfloat coordinates
        typedef TriangleStrip<FloatVec3> TriangleStrip3D;

    } // ns gl
    
} // ns gpc