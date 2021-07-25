#pragma once
#include "Event.h"

namespace FractalViewer {

	enum class KeyboardFlag {

		NONE,
		PRESSED,
		REPEATED,
		RELEASED
	};

	class KeyboardEvent : public Event {

	private:
		KeyboardFlag flag;
		uint32_t keyCode;

	public:
		KeyboardEvent(KeyboardFlag flag, uint32_t keyCode);

		uint32_t GetKeyCode() const;
		bool IsPressed() const;
		bool IsReleased() const;

		std::string GetInfo() const;
	};
}


