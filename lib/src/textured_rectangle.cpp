#include <glbinding/gl/gl.h>
using namespace gl;

#include <gpc/gl/textured_rectangle.hpp>

namespace gpc {
    
    namespace gl {
        
        const VertexAttribute _texturedRectangleAttributes[2] = {
            { GL_FLOAT, 4, 0},
            { GL_FLOAT, 4, 8}
        };
        
    } // ns gl
    
} // ns gpc