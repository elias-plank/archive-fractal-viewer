#include "MouseEvent.h"
#include <string>

namespace FractalViewer {

	MouseClickEvent::MouseClickEvent(MouseClickedFlag flag, uint32_t button) {

		this->flag = flag;
		this->button = button;
	}

	uint32_t MouseClickEvent::GetMouseButton() const {

		return button;
	}

	bool MouseClickEvent::IsPressed() const {

		return flag == MouseClickedFlag::PRESSED;
	}

	bool MouseClickEvent::IsReleased() const {

		return flag == MouseClickedFlag::RELEASED;
	}

	std::string MouseClickEvent::GetInfo() const {
		
		return "[MOUSECLICK] [" + std::to_string(button) + "]";
	}

	MouseMoveEvent::MouseMoveEvent(float xPos, float yPos) {

		this->xPos = xPos;
		this->yPos = yPos;
	}

	float MouseMoveEvent::GetX() const {

		return xPos;
	}

	float MouseMoveEvent::GetY() const {

		return yPos;
	}

	std::string MouseMoveEvent::GetInfo() const {

		return "[MOUSEMOVE] [" + std::to_string(xPos) + "," + std::to_string(yPos) + "]";
	}

	MouseScrollEvent::MouseScrollEvent(float xOffset, float yOffset) {

		this->xOffset = xOffset;
		this->yOffset = yOffset;
	}

	float MouseScrollEvent::GetX() const {

		return xOffset;
	}

	float MouseScrollEvent::GetY() const {

		return yOffset;
	}
	std::string MouseScrollEvent::GetInfo() const {

		return "[MOUSESCROLL] [" + std::to_string(xOffset) + "," + std::to_string(yOffset) + "]";
	}
}