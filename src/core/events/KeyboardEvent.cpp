#include "KeyboardEvent.h"
#include <string>

namespace FractalViewer {

	KeyboardEvent::KeyboardEvent(KeyboardFlag flag, uint32_t keyCode) {

		this->flag = flag;
		this->keyCode = keyCode;
	}

	uint32_t KeyboardEvent::GetKeyCode() const {

		return keyCode;
	}

	bool KeyboardEvent::IsPressed() const {

		return flag == KeyboardFlag::PRESSED || flag == KeyboardFlag::REPEATED;
	}

	bool KeyboardEvent::IsReleased() const {
	
		return flag == KeyboardFlag::RELEASED;
	}

	std::string KeyboardEvent::GetInfo() const {

		return "[KEYBOARD] [" + std::to_string(keyCode) + "]";
	}
}