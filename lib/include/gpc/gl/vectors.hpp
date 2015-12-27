#pragma once

#include <array>

namespace gpc {

    namespace gl {

        // TODO: template parameter for element type
        template <typename ElemT = GLfloat, int VectorSize = 2>
        struct _vector2_base {
            constexpr _vector2_base(ElemT x_, ElemT y_) : _elems{ x_, y_ } {}
            constexpr _vector2_base(std::array<ElemT, VectorSize> &&vals) : _elems{ std::move(vals) } {}
            auto& x() { return _elems[0]; }
            auto& y() { return _elems[1]; }
            std::array<ElemT, VectorSize> _elems;
        };

        template <typename ElemT = GLfloat, int VectorSize = 3>
        struct _vector3_base : public _vector2_base<ElemT, VectorSize> {
            //_vector3_base(GLfloat x_, GLfloat y_, GLfloat z_) : _vector2_base{ x_, y_ }, _elems[2]{ z_ } {}
            using _vector2_base<ElemT, VectorSize>::_vector2_base;
            auto& z() { return _elems[2]; }
        };

        template <typename ElemT = GLfloat, int VectorSize = 4>
        struct _vector4_base : public _vector3_base<ElemT, VectorSize> {
            //_vector4_base(GLfloat x_, GLfloat y_, GLfloat z_, GLfloat w_ = 1) : _vector3_base{ x_, y_, z_ }, _elems[3]{ w_ } {}
            using _vector3_base<ElemT, VectorSize>::_vector3_base;
            auto& w() { return _elems[3]; }
        };

        using vec2 = _vector2_base<>;
        using vec3 = _vector3_base<>;
        using vec4 = _vector4_base<>;

    } // ns gl

} // ns gl