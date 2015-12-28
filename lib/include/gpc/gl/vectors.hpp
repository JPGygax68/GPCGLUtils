#pragma once

#include <array>

namespace gpc {

    namespace gl {

        template <typename ElemT = GLfloat, int Size = 2>
        class _vector2_base: public std::array<ElemT, Size> {
        public:
            using element_type = ElemT;
            static constexpr int defined_size = Size;

            constexpr _vector2_base() { fill(0); }
            constexpr _vector2_base(ElemT x_, ElemT y_) : std::array<ElemT, Size>({ x_, y_ }) {}
            template <int Size_>
            constexpr _vector2_base(const ElemT (&arr)[Size_]) { 
                std::copy(std::begin(arr), std::begin(arr) + std::min(Size, Size_), std::begin(*this)); 
            }

            auto& x() { return at(0); }
            auto& y() { return at(1); }

            // Must be explicit otherwise would conflict with operator []
            explicit operator const ElemT *() const { return &at(0); }
            explicit operator ElemT *() { return &at(0); }

        protected:
            constexpr explicit _vector2_base(const std::array<ElemT, 2> &from) { 
                std::copy(std::begin(from), std::end(from), std::begin(*this)); 
            }

            template <typename ElemT_, int Size_> friend class _vector2_base;
            template <typename ElemT_, int Size_> friend class _vector3_base;
            template <typename ElemT_>            friend class _vector4_base;
        };

        template <typename ElemT = GLfloat, int Size = 3>
        class _vector3_base : public _vector2_base<ElemT, Size> {
        public:
            constexpr _vector3_base() : _vector2_base<ElemT, Size>() {}
            constexpr _vector3_base(ElemT x_, ElemT y_, ElemT z_) : _vector2_base{ { x_, y_, z_ } } {}
            using _vector2_base<ElemT, Size>::_vector2_base;
            constexpr _vector3_base(const _vector2_base<ElemT, 2> &from) { 
                std::copy(std::begin(from), std::end(from), std::begin(*this));
                at(2) = 0;
            }
            auto& z() { return at(2); }
        };

        template <typename ElemT = GLfloat>
        class _vector4_base : public _vector3_base<ElemT, 4> {
        public:
            constexpr _vector4_base() : _vector3_base<ElemT, 4>({0, 0, 0, 1}) {}
            constexpr _vector4_base(ElemT x_, ElemT y_, ElemT z_ = 0) : _vector3_base{ { x_, y_, z_ } } { at(3) = 1; }
            constexpr _vector4_base(ElemT x_, ElemT y_, ElemT z_, ElemT w_) : _vector3_base{ { x_, y_, z_, w_ } } {}
            constexpr _vector4_base(const ElemT (&arr)[4]) : _vector3_base<ElemT, 4>(arr) {}
            constexpr _vector4_base(const ElemT (&arr)[3]) : _vector3_base<ElemT, 4>(arr[0], arr[1], arr[2]) { at(3) = 1; }
            constexpr _vector4_base(const ElemT (&arr)[2]) : _vector3_base<ElemT, 4>(arr[0], arr[1]) { at(2) = 0, at(3) = 1; }
            constexpr _vector4_base(std::array<ElemT, 4> &&vals) : _vector3_base<ElemT, 4>(std::move(vals)) {}
            constexpr _vector4_base(const _vector3_base<ElemT, 3> &from) {
                std::copy(std::begin(from), std::end(from), std::begin(*this));
                at(3) = 1;
            }
            auto& w() { return at(3); }
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