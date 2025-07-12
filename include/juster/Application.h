#pragma once

#include <memory>

namespace Juster {

class UIManager;

/**
 * @brief Core application class that manages the main application lifecycle
 */
class Application {
public:
    /**
     * @brief Initialize the application
     * @return true if initialization was successful, false otherwise
     */
    bool initialize();

    /**
     * @brief Run the main application loop
     * @return exit code (0 for success)
     */
    int run();

    /**
     * @brief Shutdown and cleanup the application
     */
    void shutdown();

    /**
     * @brief Get the singleton instance of the application
     * @return Reference to the application instance
     */
    static Application& getInstance();

    /**
     * @brief Request application to quit
     */
    void requestQuit() { m_isRunning = false; }

private:
    Application() = default;
    ~Application() = default;
    
    // Delete copy constructor and assignment operator
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    bool m_isInitialized = false;
    bool m_isRunning = false;
    
    std::unique_ptr<UIManager> m_uiManager;
};

} // namespace Juster