#include <glbinding/gl/gl.h>
using namespace gl;

#include <gpc/gl/textured_rectangle.hpp>

namespace gpc {
    
    namespace gl {
        
        /** CAVEAT: the indices uses here (0 for vertex coordinates, 8 for texture coordinates) are
            not quite arbitrary: they are the indices defined by NVidia for their proprietary form of
            fixed-pipeline compatibility - see "Vertex Attribute Aliasing" in 
            http://developer.download.nvidia.com/opengl/glsl/glsl_release_notes.pdf. With NVidia GL
            drivers ONLY, this should allow shaders to access fixed-pipeline vertex and texture
            coordinates.
            This is not the correct way of doing things. The correct way would be to write separate
            shader implementations, one using a compatibility profile to access fixed pipeline vertex 
            attributes, and another using a core profile to access vertex attributes at arbitrary
            indices defined by the programmer.
         */
        const VertexAttribute _nvFPTexRectAttribs[2] = {
            { GL_FLOAT, 4, 0},
            { GL_FLOAT, 4, 8}
        };
        
    } // ns gl
    
} // ns gpc