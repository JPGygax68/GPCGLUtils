#pragma once

#include <array>

namespace gpc {

    namespace gl {

        template <typename ElemT = GLfloat, int VectorSize = 2>
        struct _vector2_base {
            constexpr _vector2_base() : _elems{} {}
            constexpr _vector2_base(ElemT x_, ElemT y_) : _elems{ x_, y_ } {}
            constexpr _vector2_base(const ElemT (&arr)[VectorSize]) { std::copy(std::begin(arr), std::end(arr), std::begin(_elems)); }
            constexpr _vector2_base(std::array<ElemT, VectorSize> &&vals) : _elems{ std::move(vals) } {}
            auto& x() { return _elems[0]; }
            auto& y() { return _elems[1]; }
            std::array<ElemT, VectorSize> _elems;
        };

        template <typename ElemT = GLfloat, int VectorSize = 3>
        struct _vector3_base : public _vector2_base<ElemT, VectorSize> {
            constexpr _vector3_base() : _vector2_base<ElemT, VectorSize>() {}
            constexpr _vector3_base(ElemT x_, ElemT y_, ElemT z_) : _vector2_base{ { x_, y_, z_ } } {}
            using _vector2_base<ElemT, VectorSize>::_vector2_base;
            auto& z() { return _elems[2]; }
        };

        template <typename ElemT = GLfloat>
        struct _vector4_base : public _vector3_base<ElemT, 4> {
            constexpr _vector4_base() : _vector3_base<ElemT, 4>({0, 0, 0, 1}) {}
            constexpr _vector4_base(ElemT x_, ElemT y_, ElemT z_, ElemT w_ = 1) : _vector3_base{ { x_, y_, z_, w_ } } {}
            constexpr _vector4_base(const ElemT (&arr)[4]) : _vector3_base<ElemT, 4>(arr) {}
            constexpr _vector4_base(std::array<ElemT, 4> &&vals) : _vector3_base<ElemT, 4>(std::move(vals)) {}
            auto& w() { return _elems[3]; }
        };

        using vec2 = _vector2_base<>;
        using vec3 = _vector3_base<>;
        using vec4 = _vector4_base<>;

    } // ns gl

} // ns gl