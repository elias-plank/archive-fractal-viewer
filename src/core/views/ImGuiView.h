#pragma once
#include "View.h"


namespace FractalViewer {

	class ImGuiView : public View {

	private:
		void* window;

	public:
		ImGuiView(void* window);
		~ImGuiView() = default;

		virtual void OnInit() override;
		virtual void OnDestroy() override;
		virtual void OnUpdate(float dt) override;
		virtual void OnGuiRender(float dt) override;
		virtual void OnEvent(const Event& e) override;

		void InitTheme();

		void Begin();
		void End();
	};
}


