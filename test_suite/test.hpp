#pragma once

#include <string>
#include <functional>

extern int test_count, fail_count;

#define CHECK(cond) if (!(cond)) throw std::runtime_error(std::string{#cond} + ": NO")

void test(const std::string &title, std::function<void(void)> func);


