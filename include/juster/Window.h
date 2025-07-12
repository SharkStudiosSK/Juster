#pragma once

#include <SDL2/SDL.h>

namespace Juster {

/**
 * @brief Window class that manages the main application window
 */
class Window {
public:
    /**
     * @brief Create and initialize the window
     * @param title Window title
     * @param width Window width
     * @param height Window height
     * @return true if creation was successful, false otherwise
     */
    bool create(const char* title, int width = 800, int height = 600);

    /**
     * @brief Destroy the window and cleanup
     */
    void destroy();

    /**
     * @brief Get the SDL window handle
     * @return SDL_Window pointer or nullptr if not created
     */
    SDL_Window* getHandle() const { return m_window; }

    /**
     * @brief Check if the window is created
     * @return true if created, false otherwise
     */
    bool isCreated() const { return m_window != nullptr; }

    /**
     * @brief Get window width
     * @return Window width in pixels
     */
    int getWidth() const { return m_width; }

    /**
     * @brief Get window height
     * @return Window height in pixels
     */
    int getHeight() const { return m_height; }

private:
    SDL_Window* m_window = nullptr;
    int m_width = 800;
    int m_height = 600;
};

} // namespace Juster