#pragma once

#include <string>
#include <vector>
#include <memory>

namespace Juster {

class Timeline;
class AnimationTools;

/**
 * @brief Represents an animation project
 */
class Project {
public:
    Project(const std::string& name = "Untitled Project");
    ~Project();

    /**
     * @brief Get project name
     */
    const std::string& getName() const { return m_name; }

    /**
     * @brief Set project name
     */
    void setName(const std::string& name) { m_name = name; }

    /**
     * @brief Get project file path
     */
    const std::string& getFilePath() const { return m_filePath; }

    /**
     * @brief Set project file path
     */
    void setFilePath(const std::string& path) { m_filePath = path; }

    /**
     * @brief Check if project has unsaved changes
     */
    bool isDirty() const { return m_isDirty; }

    /**
     * @brief Mark project as dirty (has unsaved changes)
     */
    void markDirty() { m_isDirty = true; }

    /**
     * @brief Mark project as clean (saved)
     */
    void markClean() { m_isDirty = false; }

    /**
     * @brief Get the timeline for this project
     */
    Timeline* getTimeline() const { return m_timeline.get(); }

    /**
     * @brief Get animation tools for this project
     */
    AnimationTools* getAnimationTools() const { return m_animationTools.get(); }

    /**
     * @brief Save project to file
     */
    bool save();

    /**
     * @brief Load project from file
     */
    bool load(const std::string& filePath);

    /**
     * @brief Get canvas dimensions
     */
    int getCanvasWidth() const { return m_canvasWidth; }
    int getCanvasHeight() const { return m_canvasHeight; }

    /**
     * @brief Set canvas dimensions
     */
    void setCanvasDimensions(int width, int height) {
        m_canvasWidth = width;
        m_canvasHeight = height;
        markDirty();
    }

private:
    std::string m_name;
    std::string m_filePath;
    bool m_isDirty = false;

    // Canvas properties
    int m_canvasWidth = 800;
    int m_canvasHeight = 600;

    // Core animation components
    std::unique_ptr<Timeline> m_timeline;
    std::unique_ptr<AnimationTools> m_animationTools;
};

} // namespace Juster