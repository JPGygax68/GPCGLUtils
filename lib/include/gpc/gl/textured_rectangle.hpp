#pragma once

#include "triangle_strip.hpp"

namespace gpc {

    namespace gl {
    
        struct TexturedRectangleVertexData {
            IntVec2 coordinates;
            IntVec2 texture_coords;
        };

        // TODO: provide specializations of this template to work with GLint as well as GLfloat

        class TexturedRectangle : public TriangleStrip<TexturedRectangleVertexData> {
        public:

            /** Uploads 2D vertices with both pixel and texel coordinates.
                TODO: optional parameters to separately define the texture corners.
             */
            void uploadVertices(GLint width, GLint height) {
                
                TexturedRectangleVertexData vertices[4] = {
                    { {     0,      0 }, {     0,      0 } },
                    { { width,      0 }, { width,      0 } },
                    { {     0, height }, {     0, height } },
                    { { width, height }, { width, height } }
                };

                TriangleStrip::uploadData(4, vertices);
            }

            void draw() {

                TriangleStrip::draw(4);
            }
        };

    } // ns gl

} // ns gpc
