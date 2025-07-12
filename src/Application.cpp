#include "juster/Application.h"
#include "juster/Window.h"
#include "juster/Renderer.h"
#include <iostream>
#include <SDL2/SDL.h>

namespace Juster {

Application& Application::getInstance() {
    static Application instance;
    return instance;
}

bool Application::initialize() {
    if (m_isInitialized) {
        return true;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_isInitialized = true;
    return true;
}

int Application::run() {
    if (!m_isInitialized) {
        std::cerr << "Application not initialized!" << std::endl;
        return 1;
    }

    Window window;
    if (!window.create("Juster")) {
        std::cerr << "Failed to create window!" << std::endl;
        return 1;
    }

    Renderer renderer;
    if (!renderer.initialize(window.getHandle())) {
        std::cerr << "Failed to initialize renderer!" << std::endl;
        return 1;
    }

    m_isRunning = true;
    SDL_Event event;

    while (m_isRunning) {
        // Handle events
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                m_isRunning = false;
            }
        }

        // Render
        renderer.clear();
        renderer.renderTestTriangle();
        renderer.present();
    }

    // Cleanup
    renderer.shutdown();
    window.destroy();

    return 0;
}

void Application::shutdown() {
    if (m_isInitialized) {
        SDL_Quit();
        m_isInitialized = false;
    }
}

} // namespace Juster