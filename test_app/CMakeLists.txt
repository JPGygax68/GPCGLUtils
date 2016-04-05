project(test_app)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_executable(${PROJECT_NAME}
  main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE libGPCGLUtils)

find_package(SDL2 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARY})

# OpenGL
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)

# GLBinding
if (NOT TARGET glbinding)
    find_package(glbinding REQUIRED)
endif()
target_include_directories(${PROJECT_NAME} PRIVATE ${GLBINDING_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLBINDING_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE GLBINDING_STATIC)

# TODO: re-enable
#add_test(NAME interactive_tests COMMAND ${PROJECT_NAME})
