#pragma once

#include <vector>
#include <memory>
#include <string>

namespace Juster {

struct Keyframe {
    float time;
    float value;
    
    Keyframe(float t, float v) : time(t), value(v) {}
};

class AnimationLayer {
public:
    AnimationLayer(const std::string& name) : m_name(name) {}
    
    const std::string& getName() const { return m_name; }
    void setName(const std::string& name) { m_name = name; }
    
    bool isVisible() const { return m_visible; }
    void setVisible(bool visible) { m_visible = visible; }
    
    float getOpacity() const { return m_opacity; }
    void setOpacity(float opacity) { m_opacity = opacity; }
    
    const std::vector<Keyframe>& getKeyframes() const { return m_keyframes; }
    void addKeyframe(float time, float value);
    void removeKeyframe(size_t index);

private:
    std::string m_name;
    bool m_visible = true;
    float m_opacity = 1.0f;
    std::vector<Keyframe> m_keyframes;
};

/**
 * @brief Timeline for managing animation keyframes and playback
 */
class Timeline {
public:
    Timeline();
    ~Timeline();

    /**
     * @brief Render the timeline UI
     */
    void render();

    /**
     * @brief Get current playback time
     */
    float getCurrentTime() const { return m_currentTime; }

    /**
     * @brief Set current playback time
     */
    void setCurrentTime(float time) { m_currentTime = time; }

    /**
     * @brief Get total duration
     */
    float getDuration() const { return m_duration; }

    /**
     * @brief Set total duration
     */
    void setDuration(float duration) { m_duration = duration; }

    /**
     * @brief Check if animation is playing
     */
    bool isPlaying() const { return m_isPlaying; }

    /**
     * @brief Start/stop playback
     */
    void play() { m_isPlaying = true; }
    void pause() { m_isPlaying = false; }
    void stop() { m_isPlaying = false; m_currentTime = 0.0f; }

    /**
     * @brief Update timeline (for playback)
     */
    void update(float deltaTime);

    /**
     * @brief Get frame rate
     */
    float getFrameRate() const { return m_frameRate; }

    /**
     * @brief Set frame rate
     */
    void setFrameRate(float fps) { m_frameRate = fps; }

    /**
     * @brief Add a new layer
     */
    void addLayer(const std::string& name);

    /**
     * @brief Get layers
     */
    const std::vector<std::unique_ptr<AnimationLayer>>& getLayers() const { return m_layers; }

private:
    float m_currentTime = 0.0f;
    float m_duration = 10.0f; // 10 seconds default
    float m_frameRate = 24.0f; // 24 FPS default
    bool m_isPlaying = false;

    std::vector<std::unique_ptr<AnimationLayer>> m_layers;
    int m_selectedLayer = -1;
};

} // namespace Juster