#pragma once

#include <memory>

#include <gpc/gl/wrappers.hpp>

namespace gpc {
    
    namespace gl {
        
        class TriangleStrip {
            
        public:

            typedef GLfloat point_t[3];
            typedef GLushort index_t;

            TriangleStrip(): vertex_buffer(0), index_buffer(0) {}

            void allocResources() {
                
                EXEC_GL(glGenBuffers, 1, &vertex_buffer);
                EXEC_GL(glGenBuffers, 1, &index_buffer);
            }
            
            void freeResources() {

                EXEC_GL(glDeleteBuffers, 1, &vertex_buffer);
                EXEC_GL(glDeleteBuffers, 1, &index_buffer);
            }
            
            void uploadData(size_t tri_count, const GLfloat *vertices) {

                uploadData(tri_count, reinterpret_cast<const point_t*>(vertices));
            }

            void uploadData(size_t tri_count, const point_t *vertices) {

                std::unique_ptr<index_t> indices( new index_t [tri_count + 2] );
                for (auto i = 0U; i < tri_count + 2; i ++) indices.get()[i] = i;

                uploadData(tri_count, vertices, indices.get());
            }

            void uploadData(size_t tri_count, const GLfloat *vertices, const index_t *indices) {

                uploadData(tri_count, reinterpret_cast<const point_t*>(vertices), indices);
            }

            void uploadData(size_t tri_count, const point_t *vertices, const index_t *indices) {

                EXEC_GL(glBindBuffer, GL_ARRAY_BUFFER, vertex_buffer);
                EXEC_GL(glBufferData, GL_ARRAY_BUFFER, (tri_count + 2) * sizeof(point_t), vertices, GL_STATIC_DRAW);
                EXEC_GL(glBindBuffer, GL_ARRAY_BUFFER, 0);

                EXEC_GL(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, index_buffer);
                EXEC_GL(glBufferData, GL_ELEMENT_ARRAY_BUFFER, (tri_count + 2) * sizeof(index_t), indices, GL_STATIC_DRAW);
                EXEC_GL(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);
            }

            void draw(size_t tri_count) {

                EXEC_GL(glEnableClientState, (GL_VERTEX_ARRAY));
                EXEC_GL(glBindBuffer, GL_ARRAY_BUFFER, vertex_buffer);
                EXEC_GL(glVertexPointer, 3, GL_FLOAT, sizeof(point_t), (void*)0);
                EXEC_GL(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, index_buffer);

                EXEC_GL(glDrawElements, GL_TRIANGLE_STRIP, tri_count + 2, GL_UNSIGNED_SHORT, (void*)0);

                EXEC_GL(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);
                EXEC_GL(glBindBuffer, GL_ARRAY_BUFFER, 0);
                EXEC_GL(glDisableClientState, (GL_VERTEX_ARRAY));
            }
            
        private:
            GLuint vertex_buffer;
            GLuint index_buffer;
        };
        
    } // ns gl
    
} // ns gpc