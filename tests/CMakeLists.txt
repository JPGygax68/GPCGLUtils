project(test_app)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_executable(${PROJECT_NAME}
  main.cpp
)

find_package(SDL2 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARY})

# OpenGL
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)

# GLBinding
find_package(glbinding REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLBINDING_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLBINDING_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE GLBINDING_STATIC)

add_test(NAME tests COMMAND test_app)
