#pragma once
#include "views/View.h"
#include "views/ImGuiView.h"
#include "Window.h"

namespace FractalViewer {

	class App {

	private:
		inline static App* instance;

	private:
		std::shared_ptr<Window> window;
		std::shared_ptr<ImGuiView> imGuiView;
		std::vector<View*> viewList;
		float lastTime;


	public:
		App(const std::string& title, uint32_t width, uint32_t height);

		void Init(const std::string& title, uint32_t width, uint32_t height);
		void Run();
		void Close();
		void OnEvent(const Event& e);
		void PushView(View* view);
		[[nodiscard]] Window* GetWindow();
		[[nodiscard]] static App* Get();
	};
}


