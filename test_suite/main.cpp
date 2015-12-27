#include <iostream>
#include <string>
#include <functional>

#include <glbinding/gl/gl.h>
using namespace gl;

#include <gpc/gl/vectors.hpp>

static int test_count = 0, fail_count = 0;

void test(const std::string &title, std::function<void(void)> func)
{
    std::cout << title << "...";

    try {
        test_count ++;

        func();

        std::cout << "...OK" << std::endl;
    }
    catch (const std::exception &e)
    {
        fail_count ++;
        std::cout << "FAILED: " << e.what() << std::endl;
    }
}

int main(int argc, char *argv[])
{
    test("vec2: can initialize with value pair", []() {
        gpc::gl::vec2 v2{ 0, 0 };
    });

    test("vec2: can initialize with wrapped std::array", []() {
        gpc::gl::vec2 v2_2{ { 0, 0 } };
    });
    
    gpc::gl::vec3 v3{ { 0, 0, 0 } };

    gpc::gl::vec4 v4{ { 0, 0, 0, 0 } };

    gpc::gl::vec4 v4_2{ { 0, 0, 0 } };

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