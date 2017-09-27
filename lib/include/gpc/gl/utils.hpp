#pragma once

#include <cassert>
#include <vector>
//#include <gpc/gl/wrappers.hpp>
#ifdef _WIN32
#define WINDOWS_LEAN_AND_MEAN
#include <Windows.h>
#endif
//#include <gl/GL.h>


namespace gpc {

    namespace gl {
    
        typedef float FloatVec2[2];
        typedef float FloatVec3[3];
        typedef float FloatVec4[4];

        typedef int32_t IntVec2[2];
        typedef int32_t IntVec3[3];
        typedef int32_t IntVec4[4];

        typedef float Matrix4[4][4];
        typedef float Matrix3[3][3];

        struct VertexAttribute {
            uint32_t type; // actually GLenum
            int32_t  count;
            int32_t index;
            // TODO: "normalized" field ?
        };

    } // ns gl
    
} // ns gpc
