#include "WindowEvent.h"
#include <string>

namespace FractalViewer {

	WindowEvent::WindowEvent(uint32_t width, uint32_t height) {

		this->width = width;
		this->height = height;
	}

	uint32_t WindowEvent::GetWidth() const {

		return width;
	}

	uint32_t WindowEvent::GetHeight() const {

		return height;
	}

	std::string WindowEvent::GetInfo() const {

		return "[WINDOW] [" + std::to_string(width) + "," + std::to_string(height) + "]";
	}
}