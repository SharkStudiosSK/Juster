#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace Juster {

/**
 * @brief Renderer class that handles OpenGL rendering operations
 */
class Renderer {
public:
    /**
     * @brief Initialize the renderer
     * @param window SDL window to render to
     * @return true if initialization was successful, false otherwise
     */
    bool initialize(SDL_Window* window);

    /**
     * @brief Shutdown and cleanup the renderer
     */
    void shutdown();

    /**
     * @brief Clear the screen with the background color
     */
    void clear();

    /**
     * @brief Present the rendered frame to the screen
     */
    void present();

    /**
     * @brief Render a simple test triangle (for now)
     */
    void renderTestTriangle();

    /**
     * @brief Check if the renderer is initialized
     * @return true if initialized, false otherwise
     */
    bool isInitialized() const { return m_isInitialized; }

private:
    bool setupOpenGL();
    unsigned int compileShader(unsigned int type, const char* source);
    unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

    SDL_Window* m_window = nullptr;
    SDL_GLContext m_glContext = nullptr;
    
    unsigned int m_shaderProgram = 0;
    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
    
    bool m_isInitialized = false;
    float m_animationTime = 0.0f;
};

} // namespace Juster