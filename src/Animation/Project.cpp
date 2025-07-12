#include "juster/Animation/Project.h"
#include "juster/Animation/Timeline.h"
#include "juster/Animation/AnimationTools.h"
#include <iostream>
#include <fstream>

namespace Juster {

Project::Project(const std::string& name) 
    : m_name(name) {
    // Initialize core components
    m_timeline = std::make_unique<Timeline>();
    m_animationTools = std::make_unique<AnimationTools>();
    
    // Add a default layer
    m_timeline->addLayer("Layer 1");
}

Project::~Project() = default;

bool Project::save() {
    if (m_filePath.empty()) {
        // TODO: Show save dialog to get file path
        m_filePath = m_name + ".juster";
    }
    
    // Simple JSON-like format for now
    std::ofstream file(m_filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for saving: " << m_filePath << std::endl;
        return false;
    }
    
    file << "{\n";
    file << "  \"name\": \"" << m_name << "\",\n";
    file << "  \"canvas_width\": " << m_canvasWidth << ",\n";
    file << "  \"canvas_height\": " << m_canvasHeight << ",\n";
    file << "  \"duration\": " << m_timeline->getDuration() << ",\n";
    file << "  \"frame_rate\": " << m_timeline->getFrameRate() << "\n";
    file << "}\n";
    
    file.close();
    
    markClean();
    std::cout << "Project saved to: " << m_filePath << std::endl;
    return true;
}

bool Project::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for loading: " << filePath << std::endl;
        return false;
    }
    
    // TODO: Implement proper JSON parsing
    // For now, just set the file path and mark as clean
    m_filePath = filePath;
    markClean();
    
    std::cout << "Project loaded from: " << filePath << std::endl;
    return true;
}

} // namespace Juster