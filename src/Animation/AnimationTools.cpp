#include "juster/Animation/AnimationTools.h"
#include <imgui.h>
#include <GL/glew.h>
#include <cmath>
#include <memory>

namespace Juster {

void Rectangle::render() {
    // Simple OpenGL rendering for rectangle
    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(GL_QUADS);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + width, position.y);
    glVertex2f(position.x + width, position.y + height);
    glVertex2f(position.x, position.y + height);
    glEnd();
    
    if (selected) {
        // Draw selection outline
        glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(position.x, position.y);
        glVertex2f(position.x + width, position.y);
        glVertex2f(position.x + width, position.y + height);
        glVertex2f(position.x, position.y + height);
        glEnd();
        glLineWidth(1.0f);
    }
}

void Circle::render() {
    // Simple OpenGL rendering for circle
    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(position.x, position.y); // Center
    
    const int segments = 32;
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float x = position.x + radius * cos(angle);
        float y = position.y + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    
    if (selected) {
        // Draw selection outline
        glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; ++i) {
            float angle = 2.0f * M_PI * i / segments;
            float x = position.x + radius * cos(angle);
            float y = position.y + radius * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
        glLineWidth(1.0f);
    }
}

AnimationTools::AnimationTools() = default;

AnimationTools::~AnimationTools() = default;

void AnimationTools::render() {
    renderToolbar();
    renderShapeProperties();
}

void AnimationTools::renderToolbar() {
    if (ImGui::Begin("Tools")) {
        // Tool buttons
        if (ImGui::Button("Select")) {
            setCurrentTool(ToolType::SELECT);
        }
        
        ImGui::SameLine();
        if (ImGui::Button("Rectangle")) {
            setCurrentTool(ToolType::RECTANGLE);
        }
        
        ImGui::SameLine();
        if (ImGui::Button("Circle")) {
            setCurrentTool(ToolType::CIRCLE);
        }
        
        ImGui::SameLine();
        if (ImGui::Button("Brush")) {
            setCurrentTool(ToolType::BRUSH);
        }
        
        ImGui::SameLine();
        if (ImGui::Button("Transform")) {
            setCurrentTool(ToolType::TRANSFORM);
        }
        
        ImGui::Separator();
        
        // Tool settings
        ImGui::Text("Current Tool: ");
        ImGui::SameLine();
        switch (m_currentTool) {
            case ToolType::SELECT: ImGui::Text("Select"); break;
            case ToolType::RECTANGLE: ImGui::Text("Rectangle"); break;
            case ToolType::CIRCLE: ImGui::Text("Circle"); break;
            case ToolType::BRUSH: ImGui::Text("Brush"); break;
            case ToolType::TRANSFORM: ImGui::Text("Transform"); break;
        }
        
        // Color picker
        float color[3] = { m_brushColor.r, m_brushColor.g, m_brushColor.b };
        if (ImGui::ColorEdit3("Color", color)) {
            m_brushColor.r = color[0];
            m_brushColor.g = color[1];
            m_brushColor.b = color[2];
        }
        
        // Brush size
        ImGui::SliderFloat("Size", &m_brushSize, 1.0f, 50.0f);
        
        ImGui::Separator();
        
        // Actions
        if (ImGui::Button("Clear All")) {
            clearShapes();
        }
        
        ImGui::End();
    }
}

void AnimationTools::renderShapeProperties() {
    if (ImGui::Begin("Properties")) {
        if (m_selectedShape) {
            ImGui::Text("Selected Shape");
            ImGui::Separator();
            
            // Position
            ImGui::InputFloat("X", &m_selectedShape->position.x);
            ImGui::InputFloat("Y", &m_selectedShape->position.y);
            
            // Color
            float color[4] = { 
                m_selectedShape->color.r, 
                m_selectedShape->color.g, 
                m_selectedShape->color.b, 
                m_selectedShape->color.a 
            };
            if (ImGui::ColorEdit4("Shape Color", color)) {
                m_selectedShape->color.r = color[0];
                m_selectedShape->color.g = color[1];
                m_selectedShape->color.b = color[2];
                m_selectedShape->color.a = color[3];
            }
            
            // Shape-specific properties
            if (auto* rect = dynamic_cast<Rectangle*>(m_selectedShape)) {
                ImGui::InputFloat("Width", &rect->width);
                ImGui::InputFloat("Height", &rect->height);
            } else if (auto* circle = dynamic_cast<Circle*>(m_selectedShape)) {
                ImGui::InputFloat("Radius", &circle->radius);
            }
        } else {
            ImGui::Text("No shape selected");
        }
        
        ImGui::End();
    }
}

void AnimationTools::renderCanvas() {
    if (ImGui::Begin("Canvas", nullptr, ImGuiWindowFlags_NoScrollbar)) {
        ImVec2 canvasPos = ImGui::GetCursorScreenPos();
        ImVec2 canvasSize = ImGui::GetContentRegionAvail();
        
        // Set up OpenGL viewport for canvas
        glViewport(
            static_cast<int>(canvasPos.x), 
            static_cast<int>(canvasPos.y), 
            static_cast<int>(canvasSize.x), 
            static_cast<int>(canvasSize.y)
        );
        
        // Set up 2D projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, canvasSize.x, canvasSize.y, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // Clear and render shapes
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        for (const auto& shape : m_shapes) {
            shape->render();
        }
        
        // Handle canvas input
        handleCanvasInput();
        
        // Reserve space for canvas in ImGui
        ImGui::InvisibleButton("Canvas", canvasSize);
        
        ImGui::End();
    }
}

void AnimationTools::handleCanvasInput() {
    ImGuiIO& io = ImGui::GetIO();
    
    if (ImGui::IsItemHovered() && io.MouseClicked[0]) {
        ImVec2 mousePos = ImGui::GetMousePos();
        ImVec2 canvasPos = ImGui::GetItemRectMin();
        
        Point2D localMousePos(
            mousePos.x - canvasPos.x,
            mousePos.y - canvasPos.y
        );
        
        switch (m_currentTool) {
            case ToolType::RECTANGLE: {
                auto rect = std::make_unique<Rectangle>();
                rect->position = localMousePos;
                rect->color = m_brushColor;
                addShape(std::move(rect));
                break;
            }
            
            case ToolType::CIRCLE: {
                auto circle = std::make_unique<Circle>();
                circle->position = localMousePos;
                circle->color = m_brushColor;
                addShape(std::move(circle));
                break;
            }
            
            case ToolType::SELECT: {
                // Find shape at mouse position
                m_selectedShape = nullptr;
                for (auto& shape : m_shapes) {
                    shape->selected = false;
                }
                
                // Simple hit testing (could be improved)
                for (auto& shape : m_shapes) {
                    float dx = localMousePos.x - shape->position.x;
                    float dy = localMousePos.y - shape->position.y;
                    
                    bool hit = false;
                    if (auto* rect = dynamic_cast<Rectangle*>(shape.get())) {
                        hit = (dx >= 0 && dx <= rect->width && dy >= 0 && dy <= rect->height);
                    } else if (auto* circle = dynamic_cast<Circle*>(shape.get())) {
                        float dist = sqrt(dx*dx + dy*dy);
                        hit = (dist <= circle->radius);
                    }
                    
                    if (hit) {
                        shape->selected = true;
                        m_selectedShape = shape.get();
                        break;
                    }
                }
                break;
            }
            
            default:
                break;
        }
    }
}

void AnimationTools::addShape(std::unique_ptr<Shape> shape) {
    m_shapes.push_back(std::move(shape));
}

} // namespace Juster