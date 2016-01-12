#include <iostream>
#include <cassert>

#include "test.hpp"

static const int indent_per_level = 2;

int test_count = 0, fail_count = 0, structure_level = 0;

static int col = 0;

static void print_indent()
{
    assert(col == 0);

    std::cout << std::string(indent_per_level*structure_level, ' ');
    col += indent_per_level * structure_level;
}

static void print(const std::string &text)
{
    std::cout << text;
    col += text.length(); // TODO: use locale to find out how many printable characters are in the string
}

void test(const std::string &title, std::function<void(void)> func)
{
    print_indent();
    print(title);

    try 
    {
        test_count++;

        func();

        std::cout << std::string(80-2-col, '.') << "OK";
    }
    catch (const std::exception &e)
    {
        fail_count++;
        std::cout << std::string(80-6-col, '.') << "FAILED" << std::endl;
        std::cout << std::string(indent_per_level * (structure_level + 1), ' ') << e.what();
    }

    std::cout << std::endl;
    col = 0;
}

void print_heading(const std::string & heading)
{
    assert(col == 0);
    std::cout << heading << std::endl;
}

