#include "juster/Animation/Timeline.h"
#include <imgui.h>
#include <algorithm>

namespace Juster {

void AnimationLayer::addKeyframe(float time, float value) {
    m_keyframes.emplace_back(time, value);
    
    // Sort keyframes by time
    std::sort(m_keyframes.begin(), m_keyframes.end(), 
        [](const Keyframe& a, const Keyframe& b) {
            return a.time < b.time;
        });
}

void AnimationLayer::removeKeyframe(size_t index) {
    if (index < m_keyframes.size()) {
        m_keyframes.erase(m_keyframes.begin() + index);
    }
}

Timeline::Timeline() {
    // Initialize with default values
}

Timeline::~Timeline() = default;

void Timeline::render() {
    if (ImGui::Begin("Timeline")) {
        // Playback controls
        if (ImGui::Button(m_isPlaying ? "Pause" : "Play")) {
            if (m_isPlaying) {
                pause();
            } else {
                play();
            }
        }
        
        ImGui::SameLine();
        if (ImGui::Button("Stop")) {
            stop();
        }
        
        ImGui::SameLine();
        ImGui::Text("Time: %.2fs", m_currentTime);
        
        // Time scrubber
        float timeSlider = m_currentTime;
        if (ImGui::SliderFloat("##Timeline", &timeSlider, 0.0f, m_duration, "%.2fs")) {
            setCurrentTime(timeSlider);
        }
        
        ImGui::Separator();
        
        // Timeline settings
        if (ImGui::CollapsingHeader("Settings")) {
            if (ImGui::InputFloat("Duration", &m_duration)) {
                m_duration = std::max(0.1f, m_duration);
            }
            
            if (ImGui::InputFloat("Frame Rate", &m_frameRate)) {
                m_frameRate = std::max(1.0f, m_frameRate);
            }
        }
        
        ImGui::Separator();
        
        // Layers
        ImGui::Text("Layers:");
        
        if (ImGui::Button("Add Layer")) {
            addLayer("Layer " + std::to_string(m_layers.size() + 1));
        }
        
        // Layer list
        for (size_t i = 0; i < m_layers.size(); ++i) {
            ImGui::PushID(static_cast<int>(i));
            
            auto& layer = m_layers[i];
            bool isSelected = (m_selectedLayer == static_cast<int>(i));
            
            if (ImGui::Selectable(layer->getName().c_str(), isSelected)) {
                m_selectedLayer = static_cast<int>(i);
            }
            
            ImGui::SameLine();
            
            // Visibility toggle
            bool visible = layer->isVisible();
            if (ImGui::Checkbox("##Visible", &visible)) {
                layer->setVisible(visible);
            }
            
            ImGui::SameLine();
            
            // Opacity slider
            float opacity = layer->getOpacity();
            ImGui::SetNextItemWidth(100);
            if (ImGui::SliderFloat("##Opacity", &opacity, 0.0f, 1.0f, "%.2f")) {
                layer->setOpacity(opacity);
            }
            
            // Show keyframes for selected layer
            if (isSelected) {
                ImGui::Indent();
                ImGui::Text("Keyframes:");
                
                const auto& keyframes = layer->getKeyframes();
                for (size_t j = 0; j < keyframes.size(); ++j) {
                    ImGui::Text("  %.2fs: %.2f", keyframes[j].time, keyframes[j].value);
                }
                
                // Add keyframe button
                if (ImGui::Button("Add Keyframe")) {
                    layer->addKeyframe(m_currentTime, 1.0f);
                }
                
                ImGui::Unindent();
            }
            
            ImGui::PopID();
        }
        
        ImGui::End();
    }
}

void Timeline::update(float deltaTime) {
    if (m_isPlaying) {
        m_currentTime += deltaTime;
        if (m_currentTime >= m_duration) {
            m_currentTime = m_duration;
            pause(); // Auto-pause at end
        }
    }
}

void Timeline::addLayer(const std::string& name) {
    m_layers.push_back(std::make_unique<AnimationLayer>(name));
}

} // namespace Juster