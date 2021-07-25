#pragma once

#include "../events/Event.h"

namespace FractalViewer {

	class View {

	public:
		View() = default;
		~View() = default;

		virtual void OnInit() = 0;
		virtual void OnDestroy() = 0;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnGuiRender(float dt) = 0;
		virtual void OnEvent(const Event& e) = 0;
	};

}

