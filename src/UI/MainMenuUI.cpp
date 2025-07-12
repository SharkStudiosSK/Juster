#include "juster/UI/MainMenuUI.h"
#include "juster/Animation/Project.h"
#include "juster/Animation/Timeline.h"
#include "juster/Animation/AnimationTools.h"
#include <imgui.h>
#include <memory>

namespace Juster {

MainMenuUI::MainMenuUI() = default;

MainMenuUI::~MainMenuUI() = default;

void MainMenuUI::render() {
    renderMenuBar();
    
    if (m_showNewProjectDialog) {
        renderNewProjectDialog();
    }
    
    if (hasProject()) {
        renderProjectView();
    }
}

void MainMenuUI::renderMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Project", "Ctrl+N")) {
                m_showNewProjectDialog = true;
            }
            
            if (ImGui::MenuItem("Open Project", "Ctrl+O")) {
                if (m_onOpenProject) {
                    m_onOpenProject();
                }
            }
            
            ImGui::Separator();
            
            bool hasProject = this->hasProject();
            if (ImGui::MenuItem("Save Project", "Ctrl+S", false, hasProject)) {
                if (m_onSaveProject) {
                    m_onSaveProject();
                }
            }
            
            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S", false, hasProject)) {
                // TODO: Implement save as
            }
            
            ImGui::Separator();
            
            if (ImGui::MenuItem("Quit", "Ctrl+Q")) {
                if (m_onQuit) {
                    m_onQuit();
                }
            }
            
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "Ctrl+Z", false, false)) {
                // TODO: Implement undo
            }
            if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) {
                // TODO: Implement redo
            }
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Animation")) {
            if (ImGui::MenuItem("Play", "Space", false, hasProject())) {
                // TODO: Implement play
            }
            if (ImGui::MenuItem("Pause", "Space", false, hasProject())) {
                // TODO: Implement pause
            }
            if (ImGui::MenuItem("Stop", "Escape", false, hasProject())) {
                // TODO: Implement stop
            }
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("About")) {
                // TODO: Show about dialog
            }
            ImGui::EndMenu();
        }
        
        ImGui::EndMainMenuBar();
    }
}

void MainMenuUI::renderNewProjectDialog() {
    if (ImGui::Begin("New Project", &m_showNewProjectDialog, ImGuiWindowFlags_Modal | ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Create a new animation project");
        ImGui::Separator();
        
        ImGui::Text("Project Name:");
        ImGui::InputText("##ProjectName", m_projectNameBuffer, sizeof(m_projectNameBuffer));
        
        ImGui::Separator();
        
        if (ImGui::Button("Create")) {
            // Create new project
            m_currentProject = std::make_unique<Project>(m_projectNameBuffer);
            m_showNewProjectDialog = false;
            
            if (m_onNewProject) {
                m_onNewProject();
            }
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("Cancel")) {
            m_showNewProjectDialog = false;
        }
        
        ImGui::End();
    }
}

void MainMenuUI::renderProjectView() {
    if (!m_currentProject) return;
    
    // Project info window
    if (ImGui::Begin("Project")) {
        ImGui::Text("Project: %s", m_currentProject->getName().c_str());
        
        if (m_currentProject->isDirty()) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "*");
        }
        
        ImGui::Separator();
        
        ImGui::Text("Canvas Size:");
        int width = m_currentProject->getCanvasWidth();
        int height = m_currentProject->getCanvasHeight();
        
        if (ImGui::InputInt("Width", &width)) {
            m_currentProject->setCanvasDimensions(width, height);
        }
        
        if (ImGui::InputInt("Height", &height)) {
            m_currentProject->setCanvasDimensions(width, height);
        }
        
        ImGui::End();
    }
    
    // Render timeline
    if (m_currentProject->getTimeline()) {
        m_currentProject->getTimeline()->render();
    }
    
    // Render animation tools
    if (m_currentProject->getAnimationTools()) {
        m_currentProject->getAnimationTools()->render();
        m_currentProject->getAnimationTools()->renderCanvas();
    }
}

void MainMenuUI::setCallbacks(
    std::function<void()> onNewProject,
    std::function<void()> onOpenProject,
    std::function<void()> onSaveProject,
    std::function<void()> onQuit
) {
    m_onNewProject = onNewProject;
    m_onOpenProject = onOpenProject;
    m_onSaveProject = onSaveProject;
    m_onQuit = onQuit;
}

} // namespace Juster