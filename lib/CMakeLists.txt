add_library(libGPCGLUtils INTERFACE)

target_include_directories(libGPCGLUtils BEFORE
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
    #$<INSTALL_INTERFACE:include> # TODO
)

set(SHADER_FILES "vertex.glsl" "fragment.glsl")

# "Embed" all shader files (convert to header files)

# Unfortunately, this requires a "dummy" target
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/dummy_main.c "int main(int argc, char *argv[]) { return 0; }")
add_executable(dummy "${CMAKE_CURRENT_BINARY_DIR}/dummy_main.c")

foreach(shader_file ${SHADER_FILES})
  target_sources(dummy PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated/${shader_file}.h")
  find_package(GPCBin2C REQUIRED)
  add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/generated/${shader_file}.h"
    COMMAND GPCBin2C -i "${CMAKE_CURRENT_SOURCE_DIR}/src/${shader_file}" -o "${CMAKE_CURRENT_BINARY_DIR}/generated/${shader_file}.h"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/${shader_file}"
  )
endforeach()

export(TARGETS libGPCGLUtils FILE libGPCGLUtils-targets.cmake)
configure_file(libGPCGLUtils-config.cmake.in libGPCGLUtils-config.cmake @ONLY)
export(PACKAGE libGPCGLUtils)

# TODO: install
