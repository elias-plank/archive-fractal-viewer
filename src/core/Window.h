#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include "events/EventList.h"

namespace FractalViewer {

	struct WindowData {
		uint32_t width;
		uint32_t height;
		std::string title;
		EventFn eventCallback;

		bool running;

		WindowData(const std::string& title, uint32_t width, uint32_t height, const EventFn& callback) {

			this->title = title;
			this->width = width;
			this->height = height;
			this->eventCallback = callback;
			this->running = true;
		}
	};

	class Window {

	private:
		GLFWwindow* window;
		std::shared_ptr<WindowData> windowData;

	public:
		Window(const std::string& title, uint32_t width, uint32_t height, const EventFn& callback);

		void Init(const std::string& title, uint32_t width, uint32_t height, const EventFn& callback);
		void Shutdown();
		void OnUpdate();

		void UpdateViewport(uint32_t width, uint32_t height);

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		std::string GetWindowTitle() const;

		glm::dvec2 GetCursorPos() const;

		bool& IsRunning() const;

		void* NativeWindow() const;
	};
}



