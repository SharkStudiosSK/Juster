#pragma once

#include <vector>
#include <memory>

namespace Juster {

enum class ToolType {
    SELECT,
    RECTANGLE,
    CIRCLE,
    BRUSH,
    TRANSFORM
};

struct Point2D {
    float x, y;
    Point2D(float x = 0, float y = 0) : x(x), y(y) {}
};

struct Color {
    float r, g, b, a;
    Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) 
        : r(r), g(g), b(b), a(a) {}
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual void render() = 0;
    
    Point2D position;
    Color color;
    bool selected = false;
};

class Rectangle : public Shape {
public:
    float width = 100.0f;
    float height = 100.0f;
    void render() override;
};

class Circle : public Shape {
public:
    float radius = 50.0f;
    void render() override;
};

/**
 * @brief Basic 2D animation tools for drawing and transforming objects
 */
class AnimationTools {
public:
    AnimationTools();
    ~AnimationTools();

    /**
     * @brief Render the tools UI
     */
    void render();

    /**
     * @brief Render the canvas where animation objects are drawn
     */
    void renderCanvas();

    /**
     * @brief Get current selected tool
     */
    ToolType getCurrentTool() const { return m_currentTool; }

    /**
     * @brief Set current tool
     */
    void setCurrentTool(ToolType tool) { m_currentTool = tool; }

    /**
     * @brief Handle mouse input on canvas
     */
    void handleCanvasInput();

    /**
     * @brief Add a shape to the canvas
     */
    void addShape(std::unique_ptr<Shape> shape);

    /**
     * @brief Get all shapes
     */
    const std::vector<std::unique_ptr<Shape>>& getShapes() const { return m_shapes; }

    /**
     * @brief Clear all shapes
     */
    void clearShapes() { m_shapes.clear(); }

    /**
     * @brief Get current brush color
     */
    const Color& getBrushColor() const { return m_brushColor; }

    /**
     * @brief Set brush color
     */
    void setBrushColor(const Color& color) { m_brushColor = color; }

    /**
     * @brief Get brush size
     */
    float getBrushSize() const { return m_brushSize; }

    /**
     * @brief Set brush size
     */
    void setBrushSize(float size) { m_brushSize = size; }

private:
    void renderToolbar();
    void renderShapeProperties();
    
    ToolType m_currentTool = ToolType::SELECT;
    Color m_brushColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
    float m_brushSize = 5.0f;
    
    std::vector<std::unique_ptr<Shape>> m_shapes;
    
    // Canvas interaction state
    bool m_isDrawing = false;
    Point2D m_lastMousePos;
    Shape* m_selectedShape = nullptr;
};

} // namespace Juster