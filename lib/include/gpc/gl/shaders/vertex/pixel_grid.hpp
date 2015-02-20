#pragma once

// TODO: replace this with the output of GPCEmbed in "header-only" mode as soon as available

#include <array>

namespace gpc {

    namespace gl {
    
        namespace shaders {
        
            namespace vertex {
            
                inline const std::string
                pixel_grid() {

                    static const char code[] = {
                        #include "shaders/vertex/pixel_grid.glsl.h"
                    };
                    static std::string s(code, sizeof(code));

                    return code;
                }

            } // ns vertex

        } // ns shaders

    } // ns gl

} // ns gpc
