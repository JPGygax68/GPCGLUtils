//#include <iostream>

#include "test.hpp"

int test_count = 0, fail_count = 0, structure_level = 0;

static int col = 0;

void test(const std::string &title, std::function<void(void)> func)
{
    std::cout << current_indent() << title;
    col = 2 * structure_level + title.length(); // TODO: use locale to find out how many characters are in the string

    try 
    {
        test_count++;

        func();

        std::cout << std::string(80-2-col, '.') << "OK" << std::endl;
    }
    catch (const std::exception &e)
    {
        fail_count++;
        std::cout << std::string(80-6-col, '.') << "FAILED" << std::endl;
        std::cout << std::string(2 * (structure_level + 1), ' ') << e.what() << std::endl;
    }
}

auto current_indent() -> std::string
{
    return std::string(2*structure_level, ' ');
}

