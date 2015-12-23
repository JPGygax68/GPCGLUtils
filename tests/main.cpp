#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include <SDL2/sdl.h>
#include <SDL2/SDL_main.h>

class sdl2_error : public std::exception {
public:
    sdl2_error(const char *context = nullptr) : std::exception(make_message(context).c_str()) {}

private:
    static auto make_message(const char *context) -> std::string {
        using namespace std::string_literals;
        std::string msg = SDL_GetError();
        if (context) msg += " "s + context;
        SDL_ClearError();
        return msg;
    }
};

struct sdl2_window_deleter {
    void operator() (SDL_Window *p) { 
        SDL_DestroyWindow(p); }
};

using sdl2_window_pointer = std::unique_ptr<SDL_Window, sdl2_window_deleter>;

struct sdl2_gl_context_deleter {
    void operator() (void *p) {
        SDL_GL_DeleteContext(p);
    }
};

using sdl2_gl_context = std::unique_ptr<void, sdl2_gl_context_deleter>;


int main(int argc, char *argv[])
{
    try {

        if (SDL_Init(SDL_INIT_VIDEO) != 0) throw new sdl2_error();

        sdl2_window_pointer main_window(SDL_CreateWindow("libGPCGLUtils test application", 
            SDL_WINDOWPOS_CENTERED_DISPLAY(0), SDL_WINDOWPOS_CENTERED_DISPLAY(0), 
            0, 0,
            SDL_WINDOW_FULLSCREEN_DESKTOP|SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL));
        if (!main_window) throw sdl2_error();

        sdl2_gl_context gl_context(SDL_GL_CreateContext(main_window.get()));

        glbinding::Binding::initialize();

        gl::glClearColor(0, 0.6f, 1, 1);
        gl::glClear(gl::GL_COLOR_BUFFER_BIT|gl::GL_DEPTH_BUFFER_BIT);
        SDL_GL_SwapWindow(main_window.get());

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