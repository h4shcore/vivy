#pragma once

#include "image.hpp"
#include "viewport.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include <string>

struct SDLDeleter {
    void operator()(SDL_Window* w) const { if (w) SDL_DestroyWindow(w); }
    void operator()(SDL_Renderer* r) const { if (r) SDL_DestroyRenderer(r); }
};

class App {
public:
    explicit App(std::string imagePath);
    ~App();

    bool init();
    void run();

private:
    std::string m_imagePath;
    bool m_running{false};
    bool m_isDragging{false};

    std::unique_ptr<SDL_Window, SDLDeleter> m_window;
    std::unique_ptr<SDL_Renderer, SDLDeleter> m_renderer;

    Image m_image;
    Viewport m_viewport;
};
