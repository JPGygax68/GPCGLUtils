project(libGPCGLUtils)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

# This library is (almost) header-only, so headers come first:
set(HEADER_FILES 
  "include/gpc/gl/utils.hpp" 
  "include/gpc/gl/vectors.hpp"
  "include/gpc/gl/triangle_strip.hpp"
  "include/gpc/gl/textured_rectangle.hpp"
  "include/gpc/gl/shader_program.hpp"
  "include/gpc/gl/shaders/vertex/pixel_grid.hpp"
  "include/gpc/gl/shaders/fragment/picture.hpp"
)

set(SOURCE_FILES "src/textured_rectangle.cpp")

set(SHADER_FILES 
  "shaders/vertex/pixel_grid.glsl" 
  "shaders/fragment/picture.glsl"
)

# Force static runtime libraries

if (0) # TODO: provide an option (or remove altogether)
foreach(flag
  CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_RELWITHDEBINFO
  CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_DEBUG_INIT
  CMAKE_CXX_FLAGS_RELEASE  CMAKE_CXX_FLAGS_RELWITHDEBINFO
  CMAKE_CXX_FLAGS_DEBUG  CMAKE_CXX_FLAGS_DEBUG_INIT)
  STRING(REPLACE "/MD"  "/MT" "${flag}" "${${flag}}")
  SET("${flag}" "${${flag}} /EHsc")
endforeach()
endif()

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES})

target_include_directories(${PROJECT_NAME} BEFORE
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
    #$<INSTALL_INTERFACE:include> # TODO
)

# "Embed" all shader files (convert to header files)

find_package(GPCBin2C REQUIRED)

set(shader_headers)
foreach(shader_file ${SHADER_FILES})
  #get_filename_component(filename "${shader_file}" NAME)
  set(in_file "${CMAKE_CURRENT_SOURCE_DIR}/${shader_file}")
  set(out_file "${CMAKE_CURRENT_BINARY_DIR}/generated/${shader_file}.h")
  #target_sources(dummy PRIVATE "${out_file}")
  target_sources(${PROJECT_NAME} PRIVATE "${out_file}")
  add_custom_command(OUTPUT "${out_file}" COMMAND GPCBin2C -i "${in_file}" -o "${out_file}" DEPENDS "${in_file}")
  #list(APPEND shader_headers "${CMAKE_CURRENT_BINARY_DIR}/generated/${shader_file}.h")
endforeach()

find_package(libGPCGLWrappers REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC libGPCGLWrappers)

# The GLbinding dependency is private - we only need the GL types
# GLBinding (OpenGL bindings)
if (TARGET GLBinding)
    target_link_libraries(${PROJECT_NAME} PRIVATE GLBinding)
else()
    find_package(GLBinding REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLBINDING_INCLUDE_DIR})
    message("GLBINDING_LIBRARIES:${GLBINDING_LIBRARIES}")
    message("GLBINDING_DEBUG_LIBRARIES:${GLBINDING_DEBUG_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        $<$<CONFIG:Release>:${GLBINDING_LIBRARIES}>
        $<$<CONFIG:Debug>:${GLBINDING_DEBUG_LIBRARIES}>)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GLBINDING_STATIC)
endif()

if (0)
export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}-targets.cmake)
configure_file(${PROJECT_NAME}-config.cmake.in ${PROJECT_NAME}-config.cmake @ONLY)
export(PACKAGE ${PROJECT_NAME})
endif()

# TODO: install
endif()
