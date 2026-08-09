#include "app.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_hints.h>
#include <iostream>
#include <utility>

App::App(std::string imagePath)
    : m_imagePath(std::move(imagePath)) {}

App::~App() {
    IMG_Quit();
    SDL_Quit();
}

bool App::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << "\n";
        return false;
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    SDL_SetHint("SDL_WAYLAND_APP_ID", "vivy");
    SDL_SetHint("SDL_VIDEO_X11_WMCLASS", "vivy");

    SDL_Window* rawWindow = SDL_CreateWindow(
        "vivy",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (!rawWindow) {
        std::cerr << "Failed to create window: " << SDL_GetError() << "\n";
        return false;
    }
    m_window.reset(rawWindow);

    SDL_Renderer* rawRenderer = SDL_CreateRenderer(
        m_window.get(), -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!rawRenderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << "\n";
        return false;
    }
    m_renderer.reset(rawRenderer);

    if (!m_imagePath.empty()) {
        if (m_image.load(m_renderer.get(), m_imagePath)) {
            int winW = 800, winH = 600;
            SDL_GetWindowSize(m_window.get(), &winW, &winH);
            m_viewport.reset(m_image.getWidth(), m_image.getHeight(), winW, winH);
        } else {
            std::cerr << "Warning: Could not load image on startup.\n";
        }
    }

    return true;
}

void App::run() {
    m_running = true;
    SDL_Event event;

    while (m_running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    m_running = false;
                    break;

                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        m_viewport.reset(
                            m_image.getWidth(), m_image.getHeight(),
                            event.window.data1, event.window.data2
                        );
                    }
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_q:
                        case SDLK_ESCAPE:
                            m_running = false;
                            break;
                        case SDLK_r: {
                            int winW, winH;
                            SDL_GetWindowSize(m_window.get(), &winW, &winH);
                            m_viewport.reset(m_image.getWidth(), m_image.getHeight(), winW, winH);
                            break;
                        }

                    case SDLK_f: {
                            Uint32 flags = SDL_GetWindowFlags(m_window.get());
                            if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) {
                                SDL_SetWindowFullscreen(m_window.get(), 0); // Back to windowed
                            } else {
                                SDL_SetWindowFullscreen(m_window.get(), SDL_WINDOW_FULLSCREEN_DESKTOP); // Fullscreen
                            }
                            break;
                        }
                    }
                    break;

                case SDL_MOUSEWHEEL: {
                    int mx, my;
                    SDL_GetMouseState(&mx, &my);
                    if (event.wheel.y > 0) {
                        m_viewport.zoom(1.15f, mx, my);
                    } else if (event.wheel.y < 0) {
                        m_viewport.zoom(1.0f / 1.15f, mx, my);
                    }
                    break;
                }

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        m_isDragging = true;
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        m_isDragging = false;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (m_isDragging) {
                        m_viewport.pan(
                            static_cast<float>(event.motion.xrel),
                            static_cast<float>(event.motion.yrel)
                        );
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(m_renderer.get(), 18, 18, 18, 255);
        SDL_RenderClear(m_renderer.get());

        if (m_image.isLoaded()) {
            SDL_Rect renderQuad = m_viewport.getRenderRect(
                m_image.getWidth(), m_image.getHeight()
            );
            SDL_RenderCopy(m_renderer.get(), m_image.getTexture(), nullptr, &renderQuad);
        }

        SDL_RenderPresent(m_renderer.get());
    }
}
