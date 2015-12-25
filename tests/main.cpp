#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include "test_window.hpp"

int main(int argc, char *argv[])
{
    try {

        if (SDL_Init(SDL_INIT_VIDEO) != 0) throw new sdl2_error();

        auto main_window = test_window::create_fullscreen_desktop();

        glbinding::Binding::initialize();

        gl::glClearColor(0, 0.6f, 1, 1);
        gl::glClear(gl::GL_COLOR_BUFFER_BIT|gl::GL_DEPTH_BUFFER_BIT);
        SDL_GL_SwapWindow(main_window.window.get());

        SDL_Delay(3000);
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }

    return 0;
}