add_executable(test_program main.cpp)

target_link_libraries(test_program PRIVATE libGPCGLUtils)

# GLBinding
find_package(glbinding REQUIRED)
target_include_directories(test_program PRIVATE ${GLBINDING_LIBRARIES})
# We only need some types and definitions
#target_link_libraries(test_program PRIVATE ${GLBINDING_LIBRARIES})
#target_compile_definitions(test_program PRIVATE GLBINDING_STATIC)

add_test(NAME test_suite COMMAND test_program)