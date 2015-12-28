#pragma once

#include <array>

namespace gpc {

    namespace gl {

        template <typename ElemT = GLfloat, int Size = 2>
        class _vector2_base {
        public:
            constexpr _vector2_base() : _elems{} {}
            constexpr _vector2_base(ElemT x_, ElemT y_) : _elems{ x_, y_ } {}
            constexpr _vector2_base(const ElemT (&arr)[Size]) { std::copy(std::begin(arr), std::end(arr), std::begin(_elems)); }
            constexpr _vector2_base(std::array<ElemT, Size> &&vals) : _elems{ std::move(vals) } {}
            auto& x() { return _elems[0]; }
            auto& y() { return _elems[1]; }
            operator const ElemT *() const { return &_elems[0]; }

        protected:
            constexpr explicit _vector2_base(const std::array<ElemT, 2> &from) { 
                std::copy(std::begin(from), std::end(from), std::begin(_elems)); 
            }

            std::array<ElemT, Size> _elems;

            template <typename ElemT_, int Size_> friend class _vector2_base;
            template <typename ElemT_, int Size_> friend class _vector3_base;
            template <typename ElemT_>            friend class _vector4_base;
        };

        template <typename ElemT = GLfloat, int Size = 3>
        class _vector3_base : public _vector2_base<ElemT, Size> {
        public:
            constexpr _vector3_base() : _vector2_base<ElemT, Size>() {}
            constexpr _vector3_base(ElemT x_, ElemT y_, ElemT z_) : _vector2_base{ { x_, y_, z_ } } {}
            constexpr _vector3_base(const _vector2_base<ElemT> &from) : _vector2_base<ElemT, Size>(from._elems) { _elems[2] = 0; }
            using _vector2_base<ElemT, Size>::_vector2_base;
            auto& z() { return _elems[2]; }
        };

        template <typename ElemT = GLfloat>
        class _vector4_base : public _vector3_base<ElemT, 4> {
        public:
            constexpr _vector4_base() : _vector3_base<ElemT, 4>({0, 0, 0, 1}) {}
            constexpr _vector4_base(ElemT x_, ElemT y_, ElemT z_, ElemT w_ = 1) : _vector3_base{ { x_, y_, z_, w_ } } {}
            constexpr _vector4_base(const ElemT (&arr)[4]) : _vector3_base<ElemT, 4>(arr) {}
            constexpr _vector4_base(const ElemT (&arr)[3]) : _vector3_base<ElemT, 4>(arr[0], arr[1], arr[2]) { _elems[3] = 1; }
            constexpr _vector4_base(std::array<ElemT, 4> &&vals) : _vector3_base<ElemT, 4>(std::move(vals)) {}
            auto& w() { return _elems[3]; }
        };

        using vec2 = _vector2_base<>;
        using vec3 = _vector3_base<>;
        using vec4 = _vector4_base<>;

        using vec2f = _vector2_base<GLfloat>;
        using vec3f = _vector3_base<GLfloat>;
        using vec4f = _vector4_base<GLfloat>;

        using vec2d = _vector2_base<GLdouble>;
        using vec3d = _vector3_base<GLdouble>;
        using vec4d = _vector4_base<GLdouble>;

    } // ns gl

} // ns gl