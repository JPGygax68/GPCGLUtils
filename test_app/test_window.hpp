#pragma once

#include <string>

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
        SDL_DestroyWindow(p);
    }
};

using sdl2_window_pointer = std::unique_ptr<SDL_Window, sdl2_window_deleter>;

struct sdl2_gl_context_deleter {
    void operator() (void *p) {
        SDL_GL_DeleteContext(p);
    }
};

// TODO: this is probably not a good idea, because a GL context should never outlive the window it was created for
using sdl2_gl_context = std::unique_ptr<void, sdl2_gl_context_deleter>;

struct test_window {
    sdl2_window_pointer window;
    sdl2_gl_context context;

    static auto create_fullscreen_desktop()->test_window;
};

inline auto test_window::create_fullscreen_desktop() -> test_window
{
    sdl2_window_pointer window(SDL_CreateWindow("libGPCGLUtils test application",
        SDL_WINDOWPOS_CENTERED_DISPLAY(0), SDL_WINDOWPOS_CENTERED_DISPLAY(0),
        0, 0,
        SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL));
    if (!window) throw sdl2_error("trying to create a window with OpenGL capability");

    sdl2_gl_context context(SDL_GL_CreateContext(window.get()));
    if (!context) throw sdl2_error("trying to create GL context for a created window");

    return test_window{ std::move(window), std::move(context) };
}

