#pragma once

#include <cassert>
#include <vector>
#include <gpc/gl/wrappers.hpp>

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

    } // ns gl
    
} // ns gpc
