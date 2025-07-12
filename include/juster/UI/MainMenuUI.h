#pragma once

#include <string>
#include <functional>
#include <memory>

namespace Juster {

class Project;

/**
 * @brief Main menu UI component for project management
 */
class MainMenuUI {
public:
    MainMenuUI();
    ~MainMenuUI();

    /**
     * @brief Render the main menu UI
     */
    void render();

    /**
     * @brief Check if a project is currently loaded
     */
    bool hasProject() const { return m_currentProject != nullptr; }

    /**
     * @brief Get the current project
     */
    Project* getCurrentProject() const { return m_currentProject.get(); }

    /**
     * @brief Set callbacks for project operations
     */
    void setCallbacks(
        std::function<void()> onNewProject,
        std::function<void()> onOpenProject,
        std::function<void()> onSaveProject,
        std::function<void()> onQuit
    );

private:
    void renderMenuBar();
    void renderNewProjectDialog();
    void renderProjectView();
    
    // Project management
    std::unique_ptr<Project> m_currentProject;
    
    // UI state
    bool m_showNewProjectDialog = false;
    char m_projectNameBuffer[256] = "New Project";
    
    // Callbacks
    std::function<void()> m_onNewProject;
    std::function<void()> m_onOpenProject;
    std::function<void()> m_onSaveProject;
    std::function<void()> m_onQuit;
};

} // namespace Juster