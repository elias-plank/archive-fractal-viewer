#include "App.h"

namespace FractalViewer {

	App::App(const std::string& title, uint32_t width, uint32_t height) {

		Init(title, width, height);
	}

	void App::Init(const std::string& title, uint32_t width, uint32_t height) {

		window = std::make_shared<Window>(title, width, height, [this](const Event& e) {

			OnEvent(e);
		});

		imGuiView = std::make_shared<ImGuiView>(window->NativeWindow());
		lastTime = 0.0f;	

		instance = this;
	}

	void App::Run() {

		imGuiView->OnInit();

		for (auto& view : viewList) {

			view->OnInit();
		}

		while (window->IsRunning()) {

			float time = static_cast<float>(glfwGetTime());
			float dt = time - lastTime;
			lastTime = time;

			for (auto& view : viewList) {

				view->OnUpdate(dt);
			}

			imGuiView->Begin();
			for (auto& view : viewList) {

				view->OnGuiRender(dt);
			}
			imGuiView->End();

			window->OnUpdate();
		}

		for (auto& view : viewList) {

			view->OnDestroy();
		}

		imGuiView->OnDestroy();
		window->Shutdown();
	}

	void App::Close() {

		window->IsRunning() = false;
	}

	void App::OnEvent(const Event& e) {

		for (auto& view : viewList) {

			view->OnEvent(e);
		}
	}

	void App::PushView(View* view) {

		viewList.push_back(view);
	}

	Window* App::GetWindow() {

		return window.get();
	}

	App* App::Get()
	{
		return instance;
	}
}
