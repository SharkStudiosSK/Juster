#include "juster/UI/UIManager.h"
#include "juster/UI/MainMenuUI.h"
#include "juster/Window.h"
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

namespace Juster {

UIManager::UIManager() = default;

UIManager::~UIManager() {
    shutdown();
}

bool UIManager::initialize(Window* window) {
    if (m_isInitialized) {
        return true;
    }

    m_window = window;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    m_imguiContext = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    if (!ImGui_ImplSDL2_InitForOpenGL(window->getHandle(), nullptr)) {
        std::cerr << "Failed to initialize ImGui SDL2 backend!" << std::endl;
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 330")) {
        std::cerr << "Failed to initialize ImGui OpenGL3 backend!" << std::endl;
        ImGui_ImplSDL2_Shutdown();
        return false;
    }

    // Create UI components
    m_mainMenu = std::make_unique<MainMenuUI>();

    m_isInitialized = true;
    return true;
}

void UIManager::shutdown() {
    if (m_isInitialized) {
        // Cleanup UI components
        m_mainMenu.reset();

        // Cleanup ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        
        if (m_imguiContext) {
            ImGui::DestroyContext(m_imguiContext);
            m_imguiContext = nullptr;
        }

        m_isInitialized = false;
    }
}

void UIManager::newFrame() {
    if (!m_isInitialized) return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void UIManager::render() {
    if (!m_isInitialized) return;

    // Render UI components
    if (m_mainMenu) {
        m_mainMenu->render();
    }

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool UIManager::processEvent(const SDL_Event& event) {
    if (!m_isInitialized) return false;

    return ImGui_ImplSDL2_ProcessEvent(&event);
}

} // namespace Juster