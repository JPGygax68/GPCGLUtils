#pragma once

#include <array>
#include <algorithm>

namespace gpc {

    namespace gl {

        template <typename ElemT = GLfloat, int Size = 2>
        class _vector2_base {
        public:
            using element_type = ElemT;
            using c_array = ElemT[Size];
            using const_c_array = const ElemT[Size];
            static constexpr size_t defined_size = Size;

            constexpr _vector2_base() : _elems({0}) {}
            constexpr _vector2_base(ElemT x_, ElemT y_ = 0) : _elems({ x_, y_ }) {}
            constexpr _vector2_base(_vector2_base &&from) = default;
            constexpr _vector2_base(const _vector2_base &from) = default;
            template <int Size_>
            constexpr _vector2_base(const _vector2_base<ElemT, Size_> &from) : _vector2_base(from._elems) {}
            template <int Size_>
            constexpr _vector2_base(const ElemT (&arr)[Size_]) {
                std::copy(std::begin(arr), std::begin(arr) + Size_, std::begin(_elems)); 
                std::fill(std::begin(_elems) + Size_, std::end(_elems), static_cast<ElemT>(0));
            }
            constexpr _vector2_base(std::array<ElemT, Size> &&vals) : _elems( std::move(vals) ) {}
            template <int Size_>
            constexpr _vector2_base(const std::array<ElemT,Size_> &arr, std::enable_if<Size_ < Size> * = nullptr) {
                std::copy(std::begin(arr), std::begin(arr) + Size_, std::begin(_elems));
                std::fill(std::begin(_elems) + Size_, std::end(_elems), static_cast<ElemT>(0));
            }

            constexpr int size() const { return Size; }

            auto& x() { return _elems[0]; }
            auto& y() { return _elems[1]; }

            const auto& operator[](int index) const { return _elems[index]; }
            auto& operator[](int index) { return _elems[index]; }

            const auto& at(int index) const { return _elems.at(index); }
            auto& at(int index) { return _elems.at(index); }

            operator const std::array<ElemT, Size>& () const { return _elems; }
            operator std::array<ElemT, Size>& () { return _elems; }

            // The following looks dirty, but is actually quite safe: the pointer returned by data()
            // does not carry the size information, but we know it from our own definition, so using 
            // reinterpret_cast<> is risk-free in this case.
            operator c_array & () { return *reinterpret_cast<c_array*>(_elems.data()); }
            operator const_c_array & () const { return *reinterpret_cast<const_c_array*>(_elems.data()); }
            
            const auto begin() const { return _elems.begin(); }
            auto begin() { return _elems.begin(); }
            const auto end() const { return _elems.end(); }
            auto end() { return _elems.end(); }

        protected:
            constexpr explicit _vector2_base(const std::array<ElemT, 2> &from) { 
                std::copy(std::begin(from), std::end(from), std::begin(_elems)); 
            }

            template <int Size_>
            ElemT (&to_ref())[Size_] { return *reinterpret_cast<const ElemT(&)[Size_] * >(_elems.data()); }

            std::array<ElemT, Size> _elems;

            template <typename ElemT_, int Size_> friend class _vector2_base;
            template <typename ElemT_, int Size_> friend class _vector3_base;
            template <typename ElemT_>            friend class _vector4_base;
        };

        template <typename ElemT = GLfloat, int Size = 3>
        class _vector3_base : public _vector2_base<ElemT, Size> {
        public:
            using _vector2_base<ElemT, Size>::_vector2_base;
            constexpr _vector3_base() : _vector2_base<ElemT, Size>() {}
            constexpr _vector3_base(ElemT x_, ElemT y_, ElemT z_) : _vector2_base({ x_, y_, z_ }) {}
            constexpr _vector3_base(const _vector2_base<ElemT, 2> &from) {
                std::copy(std::begin(from._elems), std::end(from._elems), std::begin(_elems));
                _elems[2] = 0; 
            }
            constexpr _vector3_base(const std::array<ElemT, 2> &arr) : _vector2_base(arr) { _elems[2] = 0; }

            auto& z() { return _elems[2]; }
        };

        template <typename ElemT = GLfloat>
        class _vector4_base : public _vector3_base<ElemT, 4> {
        public:
            using _vector3_base::_vector3_base;
            constexpr _vector4_base() : _vector3_base() { _elems[3] = 1; } // needed because we define our own ctors
            constexpr _vector4_base(ElemT x_, ElemT y_, ElemT z_) : _vector3_base({ x_, y_, z_, 1 }) {} // must replace because of w = 1
            constexpr _vector4_base(ElemT x_, ElemT y_, ElemT z_, ElemT w_) : _vector3_base({ x_, y_, z_, w_ }) {} // the new ctor
            constexpr _vector4_base(std::array<ElemT, 4> &&vals) : _vector3_base(std::move(vals)) {}
            template <int Size_>
            constexpr _vector4_base(const _vector2_base<ElemT, Size_> &from) : _vector4_base(from._elems) {}
            template <int Size_>
            constexpr _vector4_base(const std::array<ElemT, Size_> &arr) : _vector3_base(arr) {
                std::copy(std::begin(arr), std::begin(arr) + Size_, std::begin(_elems));
                std::fill(std::begin(_elems) + Size_, std::end(_elems) - 1, static_cast<ElemT>(0));
                _elems[3] = 1;
            }
            constexpr _vector4_base(const ElemT(&arr)[4]) {
                std::copy(std::begin(arr), std::end(arr), std::begin(_elems));
            }
            template <int Size_>
            constexpr _vector4_base(const ElemT(&arr)[Size_]) {
                std::copy(std::begin(arr), std::begin(arr) + Size_, std::begin(_elems));
                std::fill(std::begin(_elems) + Size_, std::end(_elems) - 1, static_cast<ElemT>(0));
                _elems[3] = 1;
            }

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