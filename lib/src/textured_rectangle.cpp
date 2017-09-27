#include <gpc/gl/utils.hpp>


// Copied from gl.h header:
/* DataType */
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_2_BYTES                        0x1407
#define GL_3_BYTES                        0x1408
#define GL_4_BYTES                        0x1409
#define GL_DOUBLE                         0x140A

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
            { GL_FLOAT, 4, 8}   // see above
        };
        
        /** The "default" vertex attributes are: 4 floats for the vertex coordinates (x,y,z,w) plus
            2 floats (u,v) for the texture coordinates.
            NOT TO BE CONFUSED with the "fixed pipeline" vertex attribute layout that is being
            mimicked by the _nvFPTexRectAttributes[] array.
         */
        const VertexAttribute _nvDefaultTexRectAttribs[2] = {
            { GL_FLOAT, 4, 0},
            { GL_FLOAT, 2, 1}
        };
    } // ns gl
    
} // ns gpc