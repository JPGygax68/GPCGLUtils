set(HEADER_FILES 
  "include/gpc/gl/utils.hpp" 
  "include/gpc/gl/triangle_strip.hpp"
  "include/gpc/gl/textured_rectangle.hpp"
  "include/gpc/gl/shader_program.hpp"
  "include/gpc/gl/shaders/vertex/pixel_grid.hpp"
  "include/gpc/gl/shaders/fragment/rgba.hpp"
)

set(SHADER_FILES 
  "shaders/vertex/pixel_grid.glsl" 
  "shaders/fragment/rgba.glsl"
)

add_library(libGPCGLUtils INTERFACE)

target_include_directories(libGPCGLUtils BEFORE
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
    #$<INSTALL_INTERFACE:include> # TODO
)

# Unfortunately, we need a dummy target so that we can generate files
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/dummy_main.cpp" "int main(int argc, char *argv[]) { return 0; }")
# Adding the header files to the dummy executable target helps when working with Visual Studio
add_executable(dummy "${CMAKE_CURRENT_BINARY_DIR}/dummy_main.cpp" ${HEADER_FILES} ${SHADER_FILES})
target_link_libraries(dummy PUBLIC libGPCGLUtils)

# "Embed" all shader files (convert to header files)

find_package(GPCBin2C REQUIRED)

set(shader_headers)
foreach(shader_file ${SHADER_FILES})
  #get_filename_component(filename "${shader_file}" NAME)
  set(in_file "${CMAKE_CURRENT_SOURCE_DIR}/${shader_file}")
  set(out_file "${CMAKE_CURRENT_BINARY_DIR}/generated/${shader_file}.h")
  target_sources(dummy PRIVATE "${out_file}")
  add_custom_command(OUTPUT "${out_file}" COMMAND GPCBin2C -i "${in_file}" -o "${out_file}" DEPENDS "${in_file}")
  #list(APPEND shader_headers "${CMAKE_CURRENT_BINARY_DIR}/generated/${shader_file}.h")
endforeach()

export(TARGETS libGPCGLUtils FILE libGPCGLUtils-targets.cmake)
configure_file(libGPCGLUtils-config.cmake.in libGPCGLUtils-config.cmake @ONLY)
export(PACKAGE libGPCGLUtils)

# TODO: install
