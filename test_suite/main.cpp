#include <iostream>
#include <string>
#include <functional>

#include <glbinding/gl/gl.h>
using namespace gl;

#include <gpc/gl/vectors.hpp>

#include "test.hpp"

int main(int argc, char *argv[])
{
    test("vec2: can be default-constructed", []() {
        gpc::gl::vec2 v;
        CHECK(v.x() == 0 && v.y() == 0);
    });
    test("vec2: can be initialized with value pair", []() {
        gpc::gl::vec2 v{ 12, 13 };
        CHECK(v.x() == 12 && v.y() == 13);
    });
    test("vec2: can be initialized with wrapped std::array", []() {
        gpc::gl::vec2 v{ { 120, 130 } };
        CHECK(v.x() == 120 && v.y() == 130);
    });
    test("vec2: can be initialized with reference to fixed-dimension C array", []() {
        GLfloat values[2] { 22, 23 };
        gpc::gl::vec2 v{ values };
        CHECK(v.x() == 22 && v.y() == 23);
    });
    test("vec2: implicitly converts to pointer", []() {
        gpc::gl::vec2 v{ {101, 102} };
        const GLfloat *p = v;
        CHECK(p[0] == 101 && p[1] == 102);
    });

    test("vec3: can be default-constructed", []() {
        gpc::gl::vec3 v;
        CHECK(v.x() == 0 && v.y() == 0 && v.z() == 0);
    });
    test("vec3: can be copy-constructed from vec2", []() {
        gpc::gl::vec2 v2{{50,51}};
        gpc::gl::vec3 v3(v2);
        CHECK(v3.x() == 50 && v3.y() == 51 && v3.z() == 0);
    });
    test("vec3: can be initialized with 3 values", []() {
        gpc::gl::vec3 v{ 999, 1000, 1001 };
        CHECK(v.x() == 999 && v.y() == 1000 && v.z() == 1001);
    });
    test("vec3: can be initialized with wrapped std::array", []() {
        gpc::gl::vec3 v{ { 11, 12, 13 } };
        CHECK(v.x() == 11 && v.y() == 12 && v.z() == 13);
    });
    test("vec3: can be initialized with reference to fixed-dimension C array", []() {
        GLfloat values[]{ 22, 23, 24 };
        gpc::gl::vec3 v{ values };
        CHECK(v.x() == 22 && v.y() == 23 && v.z() == 24);
    });

    test("vec4: can be default-constructed", []() {
        gpc::gl::vec4 v;
        CHECK(v.x() == 0 && v.y() == 0 && v.z() == 0 && v.w() == 1);
    });
    test("vec4: can be initialized with 4 values", []() {
        gpc::gl::vec4 v{ 2000, 2001, 2002, 2003 };
        CHECK(v.x() == 2000 && v.y() == 2001 && v.z() == 2002 && v.w() == 2003);
    });
    test("vec4: can be initialized with 3 values", []() {
        gpc::gl::vec4 v{ 3000, 3001, 3002 };
        CHECK(v.x() == 3000 && v.y() == 3001 && v.z() == 3002 && v.w() == 1);
    });
    test("vec4: can be initialized with reference to fixed-dimension C array", []() {
        GLfloat values[]{ 22, 23, 24, 3 };
        gpc::gl::vec4 v{ values };
        CHECK(v.x() == 22 && v.y() == 23 && v.z() == 24 && v.w() == 3);
    });
    test("vec4: can be initialized with reference to fixed-dimension C array of size 3", []() {
        GLfloat values[]{ 32, 33, 34 };
        gpc::gl::vec4 v{ values };
        CHECK(v.x() == 32 && v.y() == 33 && v.z() == 34 && v.w() == 1);
    });
    test("vec4: can be initialized with wrapped std::array", []() {
        gpc::gl::vec4 v{ { 4000, 4001, 4002, 2 } };
        CHECK(v.x() == 4000 && v.y() == 4001 && v.z() == 4002 && v.w() == 2);
    });

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