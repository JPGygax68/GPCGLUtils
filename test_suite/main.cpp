#include <iostream>
//#include <string>
#include <memory>
#include <type_traits>

#include <glbinding/gl/gl.h>
using namespace gl;

#include <gpc/gl/vectors.hpp>

#include "test.hpp"

template <typename Type>
static Type get_element(const Type *val, int index) { return val[index]; }

template <typename Vector, size_t Size>
void test_vector_class_size_2_or_higher()
{
    static_assert(std::is_default_constructible<Vector>::value, "vector type is not default-constructible");
    static_assert(std::is_copy_constructible<Vector>::value   , "vector type is not copy-constructible"   );
    static_assert(std::is_move_constructible<Vector>::value   , "vector type is not move-constructible"   );

    test("can be default-constructed", []() {
        Vector v;
        CHECK(v.x() == 0 && v.y() == 0);
    });
    test("copy-constructed instance has same values as original", []() {
        Vector v1{ { 1, 2 }};
        Vector v2{ v1 };
        CHECK(v2.x() == 1 && v2.y() == 2);
    });
    test("can be initialized with value pair", []() {
        Vector v{ 12, 13 };
        CHECK(v.x() == 12 && v.y() == 13);
    });
    test("move-constructed instance has correct values", []() {
        Vector v2{ Vector{3, 4} };
        CHECK(v2.x() == 3 && v2.y() == 4);
    });
    test("can be initialized with std::array literal of size 2", []() {
        Vector v{ { 120, 130 } };
        CHECK(v.x() == 120 && v.y() == 130);
    });
    test("can be initialized with reference to fixed-dimension C array of size 2", []() {
        Vector::element_type values[2]{ 22, 23 };
        Vector v{ values };
        CHECK(v.x() == 22 && v.y() == 23);
    });
    test("implicitly converts to reference to std::array", []() {
        Vector v{ { 101, 102 } };
        std::array<Vector::element_type, Size> &a = v;
        CHECK(a[0] == 101 && a[1] == 102);
    });
    test("can be passed as argument to function expecting const pointer", []() {
        Vector v{ { 101, 102 } };
        CHECK(get_element<Vector::element_type>(v, 0) == 101);
        CHECK(get_element<Vector::element_type>(v, 1) == 102);
    });
    test("can be accessed via [] operator", []() {
        Vector v{ 15, 16 };
        CHECK(v[0] == 15 && v[1] == 16);
    });
    test("size() value matches defined vector size", []() {
        Vector v;
        CHECK(v.size() == Size);
        Vector v2{ 1, 2 };
        CHECK(v2.size() == Size);
    });
#ifdef _DEBUG
    test("(DEBUG) at() throws if argument is negative", []() {
        Vector v;
        bool has_thrown = false;
        try {
            Vector::element_type dummy = v.at(-1);
        }
        catch (const std::exception &) {
            has_thrown = true;
        }
        CHECK(has_thrown);
    });
    test("(DEBUG) at() throws out_of_range if argument is equal to size", []() {
        Vector v;
        bool has_thrown = false;
        try {
            Vector::element_type dummy = v.at(Size);
        }
        catch (const std::out_of_range &) {
            has_thrown = true;
        }
        CHECK(has_thrown);
    });
#endif
}

template <typename Vector, size_t Size>
void test_vector_class_size_3_or_higher()
{
    test_vector_class_size_2_or_higher<Vector, Size>();

    test("can be copy-constructed from vector of size 2", []() {
        gpc::gl::_vector2_base<Vector::element_type> v2{ { 50, 51 } };
        Vector v3{ v2 };
        CHECK(v3.x() == 50 && v3.y() == 51 && v3.z() == 0);
    });
    test("can be initialized with 3 literal values", []() {
        Vector v{ 999, 1000, 1001 };
        CHECK(v.x() == 999 && v.y() == 1000 && v.z() == 1001);
    });
    test("can be initialized with wrapped std::array of size 3", []() {
        Vector v{ { 11, 12, 13 } };
        CHECK(v.x() == 11 && v.y() == 12 && v.z() == 13);
    });
    test("can be initialized with reference to fixed-dimension C array of size 3", []() {
        Vector::element_type values[]{ 22, 23, 24 };
        Vector v{ values };
        CHECK(v.x() == 22 && v.y() == 23 && v.z() == 24);
    });
}

template <typename Vector, int Size>
void test_vector_class_size_4()
{
    test_vector_class_size_3_or_higher<Vector, 4>();

    test("can be initialized with 4 literal values", []() {
        Vector v{ 2000, 2001, 2002, 2003 };
        CHECK(v.x() == 2000 && v.y() == 2001 && v.z() == 2002 && v.w() == 2003);
    });
    test("can be initialized with 3 values, w set to 1 automatically", []() {
        Vector v{ 3000, 3001, 3002 };
        CHECK(v.x() == 3000 && v.y() == 3001 && v.z() == 3002 && v.w() == 1);
    });
    test("when initialized from std::array of size 3, w set to 1 automatically", []() {
        Vector v{ std::array<Vector::element_type, 3>{4000, 4001, 4002} };
        CHECK(v.x() == 4000 && v.y() == 4001 && v.z() == 4002 && v.w() == 1);
    });
    test("can be initialized with reference to fixed-dimension C array of size 4", []() {
        Vector::element_type values[]{ 22, 23, 24, 3 };
        Vector v{ values };
        CHECK(v.x() == 22 && v.y() == 23 && v.z() == 24 && v.w() == 3);
    });
    test("can be initialized with reference to fixed-dimension C array of size 3", []() {
        Vector::element_type values[]{ 32, 33, 34 };
        Vector v{ values };
        CHECK(v.x() == 32 && v.y() == 33 && v.z() == 34 && v.w() == 1);
    });
    test("can be initialized with std::array literal of size 4", []() {
        Vector v{ std::array<Vector::element_type, 4>{ 4000, 4001, 4002, 2 } };
        CHECK(v.x() == 4000 && v.y() == 4001 && v.z() == 4002 && v.w() == 2);
    });
}

int main(int argc, char *argv[])
{
#ifdef _MSC_VER
    _CrtSetReportMode(_CRT_ASSERT, 0);
#endif

    print_heading("Testing vector type \"vec2\"");
    {
        level_guard lg;
        test_vector_class_size_2_or_higher<gpc::gl::vec2, 2>();
    }
    print_heading("Testing vector type \"vec2d\"");
    {
        level_guard lg;
        test_vector_class_size_2_or_higher<gpc::gl::vec2d, 2>();
    }

    print_heading("Testing vector type \"vec3\"");
    {
        level_guard lg;
        test_vector_class_size_3_or_higher<gpc::gl::vec3, 3>();
    }
    print_heading("Testing vector type \"vec3d\"");
    {
        level_guard lg;
        test_vector_class_size_3_or_higher<gpc::gl::vec3d, 3>();
    }

    print_heading("Testing vector type \"vec4\"");
    {
        level_guard lg;
        test_vector_class_size_4<gpc::gl::vec4, 4>();
    }
    print_heading("Testing vector type \"vec4d\"");
    {
        level_guard lg;
        test_vector_class_size_4<gpc::gl::vec4d, 4>();
    }


    std::cout << std::endl;
    std::cout << test_count << " tests run, " << fail_count << " failed, " << test_count - fail_count << " successful." << std::endl;
    std::cout << std::endl;
    std::cout << "Overall test result: " << (fail_count > 0 ? "FAILED" : "PASSED") << std::endl;

    std::cout << std::endl;
    std::cout << "Press RETURN to terminate" << std::endl;
    char ch;
    std::cin >> std::noskipws >> ch;

    return fail_count > 0 ? 1 : 0;
}