#pragma once

#include <cassert>
#include <vector>
//#include <gpc/gl/wrappers.hpp>
#ifdef _WIN32
#define WINDOWS_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include <gl/GL.h>


namespace gpc {

    namespace gl {
    
        typedef GLfloat FloatVec2[2];
        typedef GLfloat FloatVec3[3];
        typedef GLfloat FloatVec4[4];

        typedef GLint IntVec2[2];
        typedef GLint IntVec3[3];
        typedef GLint IntVec4[4];

        typedef GLfloat Matrix4[4][4];
        typedef GLfloat Matrix3[3][3];

        struct VertexAttribute {
            GLenum type;
            GLint  count;
            GLint index;
            // TODO: "normalized" field ?
        };

    } // ns gl
    
} // ns gpc
