#pragma once

#include <string>
#include <functional>
#include <iostream>

extern int test_count, fail_count, structure_level;

#define CHECK(cond) if (!(cond)) throw std::runtime_error(std::string{#cond} + ": NO")

void test(const std::string &title, std::function<void(void)> func);

void print_heading(const std::string &heading);

class level_guard {
public:
    level_guard() { structure_level ++; }
    ~level_guard() { structure_level --; }
};

#ifdef NOT_DEFINED

class pass {};
class fail {};

class test_logger {
public:
    test_logger() : col{ 0 } {}

    template <typename Type>
    auto& operator <<(const Type &data)
    {
        auto text = std::to_string(data);
        std::cout << text;
        return *this;
    }

    template <>
    auto& operator << (const pass &)
    {
        test_count ++;
        std::cout << "...OK" << std::endl;
        return *this;
    }

    template <>
    auto& operator << (const fail &)
    {
        test_count++;
        fail_count++;
        std::cout << "...FAILED" << std::endl;
        return *this;
    }

private:
    int col;
};

#endif
