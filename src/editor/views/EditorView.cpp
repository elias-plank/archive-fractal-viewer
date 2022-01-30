#include "EditorView.h"
#include "../../core/App.h"
#include "../../core/util/File.h"

namespace FractalViewer {

	void EditorView::OnInit() {

		iterationDepth = 100;
		zoom = 0.5;
		center = glm::dvec2(-0.5, 0.0);

		auto w = App::Get()->GetWindow()->GetWidth();
		auto h = App::Get()->GetWindow()->GetHeight();
		viewportFramebuffer = std::make_shared<Framebuffer>(w, h);

		vertexArray = std::make_shared<VertexArray>();
		vertexBuffer = std::make_shared<VertexBuffer>();
		elementBuffer = std::make_shared<ElementBuffer>();
		shader = std::make_shared<Shader>();

		vertexBuffer->SetLayout({
			{ ShaderDataType::Float2 } // position
		});

		vertexArray->SetVertexBuffer(vertexBuffer);
		vertexArray->SetElementBuffer(elementBuffer);
		shader->Load("assets/shader/mandelVertex.glsl", "assets/shader/mandelFrag.glsl");

		vertices = {

			{ -1.0f, -1.0f },
			{  1.0f, -1.0f },
			{  1.0f,  1.0f },
			{ -1.0f,  1.0f }
		};

		indices = {

			0, 1, 2, 
			2, 0, 3
		};

		vertexBuffer->SetData(vertices.data(), static_cast<uint32_t>(vertices.size() * sizeof(float) * 2));
		elementBuffer->SetData(indices.data(), static_cast<uint32_t>(indices.size()));

		shader->SetInt("depth", iterationDepth);
		shader->SetDouble2("screenSize", { w, h });
		shader->SetDouble2("center", center);
		shader->SetDouble("zoom", zoom);
		shader->SetInt("theme", 0);
	}

	void EditorView::OnDestroy() {


	}

	void EditorView::OnUpdate(float dt) {

		// All Drawing has to occur between Framebuffer bindings, will be rendered as texture
		viewportFramebuffer->Bind();

		Renderer::Clear();
		Renderer::DrawIndexed(vertexArray, elementBuffer, shader, GL_TRIANGLES);

		viewportFramebuffer->Unbind();
	}

	void EditorView::OnGuiRender(float dt) {

		// The ImGui code has to be in between these to function calls, otherwise it won't be visible
		BeginDockSpace();

		DrawMenuBar();
		DrawSettings(dt);
		DrawViewport();

		EndDockSpace();
	}

	void EditorView::OnEvent(const Event& e) {

		auto window = dynamic_cast<const WindowEvent*>(&e);
		auto scroll = dynamic_cast<const MouseScrollEvent*>(&e);
		auto key = dynamic_cast<const KeyboardEvent*>(&e);
		auto mouse = dynamic_cast<const MouseClickEvent*>(&e);

		if (window) {

			auto w = window->GetWidth();
			auto h = window->GetHeight();

			viewportFramebuffer->Resize(w, h);
		}
		else if (scroll) {

			zoom += scroll->GetY() * 0.1L * zoom;

			if (zoom < 0.1) {

				zoom = 0.1;
			}

			shader->SetDouble("zoom", zoom);
		}
		else if (key) {

			if (key->IsPressed()) {

				double off = 0.1 / zoom;
				auto keyCode = key->GetKeyCode();

				if (keyCode == GLFW_KEY_A || keyCode == GLFW_KEY_LEFT) {

					center.x -= off;
				}
				else if (keyCode == GLFW_KEY_S || keyCode == GLFW_KEY_DOWN) {

					center.y -= off;
				}
				else if (keyCode == GLFW_KEY_D || keyCode == GLFW_KEY_RIGHT) {

					center.x += off;
				}
				else if (keyCode == GLFW_KEY_W || keyCode == GLFW_KEY_UP) {

					center.y += off;
				}

				shader->SetDouble2("center", center);
			}
		}
	}

	void EditorView::DrawMenuBar() {

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) {

					App::Get()->Close();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
	}

	void EditorView::DrawSettings(float dt) {

		ImGui::Begin("Settings");

		auto w = ImGui::GetContentRegionAvail().x;
		auto h = ImGui::GetFontSize() * 1.4f;

		ImGui::PushItemWidth(w);
		
		if (ImGui::CollapsingHeader("Performance", ImGuiTreeNodeFlags_DefaultOpen)) {

			ImGui::Text("FPS: %f", 1.0f / dt);
		}

		if (ImGui::CollapsingHeader("Fractal Settings", ImGuiTreeNodeFlags_DefaultOpen)) {

			ImGui::Text("Depth (max iterations)");

			if (ImGui::DragInt("Depth", &iterationDepth, 1, 1, 10000)) {

				if (iterationDepth <= 10000 && iterationDepth > 0) {

					shader->SetInt("depth", iterationDepth);
				}
			}

			ImGui::Text("Zoom: %lf", zoom);
			ImGui::Text("Colortheme");

			const char* items[] = { "Cold", "Warm" };
			static const char* current = "Cold";

			if (ImGui::BeginCombo("##combo", current)) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < IM_ARRAYSIZE(items); n++)
				{
					bool isSelected = (current == items[n]); // You can store your selection however you want, outside or inside your objects
					
					if (ImGui::Selectable(items[n], isSelected)) {

						current = items[n];
						if (isSelected) {

							ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
						}
					}
				}

				if (strcmp(current, "Cold") == 0) {

					shader->SetInt("theme", 0);
				}
				if (strcmp(current, "Warm") == 0) {

					shader->SetInt("theme", 1);
				}
				ImGui::EndCombo();
			}

			if (ImGui::Button("Reset Settings", ImVec2(w, h))) {

				iterationDepth = 100;
				zoom = 0.5;
				center = glm::dvec2(-0.5, 0.0);

				shader->SetDouble2("center", center);
				shader->SetDouble("zoom", zoom);
				shader->SetInt("depth", iterationDepth);
			}
		}

		if (ImGui::CollapsingHeader("Export", ImGuiTreeNodeFlags_DefaultOpen)) {

			static int exportWidth = 1920;
			static int exportHeight = 1080;
			static int exportDepth = 500;

			auto width = App::Get()->GetWindow()->GetWidth();
			auto height = App::Get()->GetWindow()->GetHeight();

			ImGui::Text("Export Image as PNG");
			ImGui::Separator();
			ImGui::Text("Resolution");
			ImGui::InputInt("Width", &exportWidth);
			ImGui::InputInt("Height", &exportHeight);
			ImGui::Text("Export Depth");
			ImGui::InputInt("Export Depth", &exportDepth);

			if (ImGui::Button("Save as PNG", ImVec2(w, h))) {

				std::string path = Util::SaveFileDialog();

				try {

					if (!path.empty()) {

						shader->SetInt("depth", exportDepth);
						shader->SetDouble2("screenSize", { exportWidth, exportHeight });
						App::Get()->GetWindow()->UpdateViewport(exportWidth, exportHeight);

						viewportFramebuffer->Bind();
						viewportFramebuffer->Resize(exportWidth, exportHeight);

						Renderer::Clear();
						Renderer::DrawIndexed(vertexArray, elementBuffer, shader, GL_TRIANGLES);
						viewportFramebuffer->SaveTexture(path);

						viewportFramebuffer->Resize(width, height);
						viewportFramebuffer->Unbind();

						shader->SetInt("depth", iterationDepth);
						shader->SetDouble2("screenSize", { width, height });
						App::Get()->GetWindow()->UpdateViewport(width, height);
					}
				}
				catch (const std::runtime_error& error) {

					ASSERT(false, error.what());
				}
			}
		}

		ImGui::PopItemWidth();
		ImGui::End();
	}

	void EditorView::DrawViewport() {

		ImGui::Begin("Viewport");

		static glm::dvec2 lastMousePosition = App::Get()->GetWindow()->GetCursorPos();
		const auto currentPosition = App::Get()->GetWindow()->GetCursorPos();
		const auto contentRegion = ImGui::GetContentRegionAvail();
		const auto windowWidth = App::Get()->GetWindow()->GetWidth();
		const auto windowHeight = App::Get()->GetWindow()->GetHeight();

		shader->SetDouble2("screenSize", { contentRegion.x, contentRegion.y });

		if (glfwGetMouseButton(reinterpret_cast<GLFWwindow*>(App::Get()->GetWindow()->GetNativeWindow()), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

			if (glm::distance(currentPosition, lastMousePosition) != 0) {

				const auto distanceVec = currentPosition - lastMousePosition;
				center.x -= (distanceVec.x / (contentRegion.x * zoom)) * windowWidth / windowHeight;
				center.y += distanceVec.y / (contentRegion.y * zoom);

				shader->SetDouble2("center", center);
			}

		}

		lastMousePosition = currentPosition;

		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(viewportFramebuffer->GetTextureId())), viewportSize, { 0, 1 }, { 1, 0 });

		ImGui::End();
	}

#pragma region ImGui DockSpace Init Code

	void EditorView::BeginDockSpace() {

		// ImGui DockSpace variables
		static bool dockspaceOpen = true;
		static bool optFullscreenPersistant = true;

		bool optFullscreen = optFullscreenPersistant;
		static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (optFullscreen) {

			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		}

		if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
			windowFlags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("EditorDock", &dockspaceOpen, windowFlags);
		ImGui::PopStyleVar();

		if (optFullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 200.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("EditorDock");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);
		}

		style.WindowMinSize.x = minWinSizeX;
	}

	void EditorView::EndDockSpace() {

		// End of DockSpace
		ImGui::End();
	}

#pragma endregion
}

