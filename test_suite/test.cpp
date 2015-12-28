#include <iostream>

#include "test.hpp"

int test_count = 0, fail_count = 0;

void test(const std::string &title, std::function<void(void)> func)
{
    std::cout << title << "...";

    try {
        test_count++;

        func();

        std::cout << "...OK" << std::endl;
    }
    catch (const std::exception &e)
    {
        fail_count++;
        std::cout << "FAILED: " << e.what() << std::endl;
    }
}

