#pragma once

#include <SDL2/SDL.h>
#include <memory>

struct ImGuiContext;

namespace Juster {

class Window;
class MainMenuUI;

/**
 * @brief UI Manager that handles Dear ImGui integration and UI components
 */
class UIManager {
public:
    UIManager();
    ~UIManager();

    /**
     * @brief Initialize the UI system
     * @param window Window to render UI on
     * @return true if initialization was successful
     */
    bool initialize(Window* window);

    /**
     * @brief Shutdown and cleanup the UI system
     */
    void shutdown();

    /**
     * @brief Start a new frame for UI rendering
     */
    void newFrame();

    /**
     * @brief Render all UI components
     */
    void render();

    /**
     * @brief Process SDL events for UI
     * @param event SDL event to process
     * @return true if event was consumed by UI
     */
    bool processEvent(const SDL_Event& event);

    /**
     * @brief Check if UI is initialized
     */
    bool isInitialized() const { return m_isInitialized; }

    /**
     * @brief Get the main menu UI component
     */
    MainMenuUI* getMainMenu() const { return m_mainMenu.get(); }

private:
    bool m_isInitialized = false;
    Window* m_window = nullptr;
    ImGuiContext* m_imguiContext = nullptr;
    
    std::unique_ptr<MainMenuUI> m_mainMenu;
};

} // namespace Juster