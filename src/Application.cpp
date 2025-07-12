#include "juster/Application.h"
#include "juster/Window.h"
#include "juster/Renderer.h"
#include "juster/UI/UIManager.h"
#include "juster/UI/MainMenuUI.h"
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

    // Initialize UI Manager
    m_uiManager = std::make_unique<UIManager>();

    m_isInitialized = true;
    return true;
}

int Application::run() {
    if (!m_isInitialized) {
        std::cerr << "Application not initialized!" << std::endl;
        return 1;
    }

    Window window;
    if (!window.create("Juster - Animation Software")) {
        std::cerr << "Failed to create window!" << std::endl;
        return 1;
    }

    Renderer renderer;
    if (!renderer.initialize(window.getHandle())) {
        std::cerr << "Failed to initialize renderer!" << std::endl;
        return 1;
    }

    // Initialize UI
    if (!m_uiManager->initialize(&window)) {
        std::cerr << "Failed to initialize UI!" << std::endl;
        return 1;
    }

    // Setup UI callbacks
    auto* mainMenu = m_uiManager->getMainMenu();
    if (mainMenu) {
        mainMenu->setCallbacks(
            []() { std::cout << "New project created!" << std::endl; },
            []() { std::cout << "Open project requested!" << std::endl; },
            []() { std::cout << "Save project requested!" << std::endl; },
            [this]() { requestQuit(); }
        );
    }

    m_isRunning = true;
    SDL_Event event;

    while (m_isRunning) {
        // Handle events
        while (SDL_PollEvent(&event) != 0) {
            // Let UI handle events first
            bool eventConsumed = m_uiManager->processEvent(event);
            
            if (!eventConsumed) {
                if (event.type == SDL_QUIT) {
                    m_isRunning = false;
                }
            }
        }

        // Start UI frame
        m_uiManager->newFrame();

        // Clear screen
        renderer.clear();

        // Render UI
        m_uiManager->render();

        // Present frame
        renderer.present();
    }

    // Cleanup
    m_uiManager->shutdown();
    renderer.shutdown();
    window.destroy();

    return 0;
}

void Application::shutdown() {
    if (m_isInitialized) {
        m_uiManager.reset();
        SDL_Quit();
        m_isInitialized = false;
    }
}

} // namespace Juster