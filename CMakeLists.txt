cmake_minimum_required(VERSION 3.0)

project(libGPCGLUtils)

add_subdirectory(lib)

enable_testing()
add_subdirectory(test_suite)
add_subdirectory(test_app)
