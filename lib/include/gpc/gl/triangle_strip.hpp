#pragma once

#include <memory>

#include <gpc/gl/wrappers.hpp>

#include "utils.hpp" // TODO: replace with "types.hpp" when that is done

namespace gpc {
    
    namespace gl {
        
        // TODO: rename, since it can now contain multiple strips ?

        template <class VertexData>
        class TriangleStrip {
            
        public:

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
            
            void uploadData(size_t vertex_count, const VertexData *vertices) {

                std::unique_ptr<index_t> indices( new index_t [vertex_count] );
                for (GLushort i = 0; i < vertex_count; i ++) indices.get()[i] = i;

                uploadData(vertex_count, vertices, vertex_count, indices.get());
            }

            void uploadData(size_t vertex_count, const VertexData *vertices, size_t index_count, const index_t *indices) {

                EXEC_GL(glBindBuffer, GL_ARRAY_BUFFER, vertex_buffer);
                EXEC_GL(glBufferData, GL_ARRAY_BUFFER, vertex_count * sizeof(VertexData), vertices, GL_STATIC_DRAW);
                EXEC_GL(glBindBuffer, GL_ARRAY_BUFFER, 0);

                EXEC_GL(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, index_buffer);
                EXEC_GL(glBufferData, GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(index_t), indices, GL_STATIC_DRAW);
                EXEC_GL(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);
            }

            void draw(size_t index_count) {

                draw(0, index_count);
            }
            
            void draw(size_t index_base, size_t index_count) {

                EXEC_GL(glEnableClientState, (GL_VERTEX_ARRAY));
                EXEC_GL(glBindBuffer, GL_ARRAY_BUFFER, vertex_buffer);
                EXEC_GL(glVertexPointer, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
                EXEC_GL(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, index_buffer);

                EXEC_GL(glDrawElements, GL_TRIANGLE_STRIP, index_count, GL_UNSIGNED_SHORT, (void*)(index_base*sizeof(GLushort)));

                EXEC_GL(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);
                EXEC_GL(glBindBuffer, GL_ARRAY_BUFFER, 0);
                EXEC_GL(glDisableClientState, (GL_VERTEX_ARRAY));
            }

        private:
            GLuint vertex_buffer;
            GLuint index_buffer;
        };
        

        // Triangle strip with only x, y GLfloat coordinates
        typedef TriangleStrip<FloatVec2> TriangleStrip2D;

        // Triangle strip with x, y, z GLfloat coordinates
        typedef TriangleStrip<FloatVec3> TriangleStrip3D;

    } // ns gl
    
} // ns gpc