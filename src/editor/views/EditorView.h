#pragma once
#include "../../core/views/View.h"
#include "../../core/gfx/Framebuffer.h"
#include "../../core/gfx/Renderer.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace FractalViewer {

    class EditorView : public View {
        
    private:

        // Framebuffer for Viewport rendering
        std::shared_ptr<Framebuffer> viewportFramebuffer;

        // Drawing variables
        std::shared_ptr<VertexArray> vertexArray;
        std::shared_ptr<VertexBuffer> vertexBuffer;
        std::shared_ptr<ElementBuffer> elementBuffer;
        std::shared_ptr<Shader> shader;
        std::vector<glm::vec2> vertices;
        std::vector<uint32_t> indices;

        // Control variables
        int iterationDepth;
        glm::dvec2 center;
        double zoom;

    public:
        virtual void OnInit() override;
        virtual void OnDestroy() override;
        virtual void OnUpdate(float dt) override;
        virtual void OnGuiRender(float dt) override;
        virtual void OnEvent(const Event& e) override;

        void DrawMenuBar();
        void DrawSettings(float dt);
        void DrawViewport();

        void BeginDockSpace();
        void EndDockSpace();
    };
}


