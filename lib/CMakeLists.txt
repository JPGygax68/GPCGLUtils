add_library(libGPCGLUtils INTERFACE)

target_sources(libGPCGLUtils INTERFACE "include/gpc/gl/utils.hpp")

target_include_directories(libGPCGLUtils BEFORE
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
