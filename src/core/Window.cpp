#include "Window.h"

namespace FractalViewer {

	Window::Window(const std::string& title, uint32_t width, uint32_t height, const EventFn& callback) {

		Init(title, width, height, callback);
	}

	void Window::Init(const std::string& title, uint32_t width, uint32_t height, const EventFn& callback) {

		windowData = std::make_shared<WindowData>(title, width, height, callback);

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		if (window == NULL) {

			fprintf(stderr, "Failed to create Window!\n");
			glfwTerminate();
			exit(-1);
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {

			fprintf(stderr, "Failed to initialize GLAD!\n");
			exit(-1);
		}

		glfwSwapInterval(1);
		glfwSetWindowUserPointer(window, windowData.get());

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			auto data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data->width = width;
			data->height = height;
			glViewport(0, 0, width, height);
			data->eventCallback(WindowEvent(width, height));
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			auto data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data->running = false;
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				data->eventCallback(MouseClickEvent(MouseClickedFlag::PRESSED, button));
				break;
			}
			case GLFW_RELEASE:
			{
				data->eventCallback(MouseClickEvent(MouseClickedFlag::RELEASED, button));

				break;
			}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data->eventCallback(MouseScrollEvent(static_cast<float>(xOffset), static_cast<float>(yOffset)));
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
		{
			auto data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data->eventCallback(MouseMoveEvent(static_cast<float>(xPos), static_cast<float>(yPos)));
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

			auto data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				data->eventCallback(KeyboardEvent(KeyboardFlag::PRESSED, key));
				break;
			}
			case GLFW_RELEASE:
			{
				data->eventCallback(KeyboardEvent(KeyboardFlag::RELEASED, key));

				break;
			}
			case GLFW_REPEAT: 
			{
				data->eventCallback(KeyboardEvent(KeyboardFlag::REPEATED, key));
				break;
			}
			}
		});
	}

	void Window::Shutdown() {

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::OnUpdate() {

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void Window::SetVSync(bool on) {

		glfwSwapInterval(on ? 1 : 0);
	}

	void Window::UpdateViewport(uint32_t width, uint32_t height) {

		glViewport(0, 0, width, height);
	}

	uint32_t Window::GetWidth() const {

		return windowData->width;
	}

	uint32_t Window::GetHeight() const {

		return windowData->height;
	}

	std::string Window::GetWindowTitle() const {

		return windowData->title;
	}

	glm::dvec2 Window::GetCursorPos() const {

		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return { x, y };
	}

	bool& Window::IsRunning() const {

		return windowData->running;
	}

	void* Window::GetNativeWindow() const {

		return window;
	}

}
