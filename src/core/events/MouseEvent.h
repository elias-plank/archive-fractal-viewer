#pragma once
#include <cstdint>
#include "Event.h"

namespace FractalViewer {

	enum class MouseClickedFlag {

		PRESSED,
		RELEASED
	};

	class MouseClickEvent : public Event {

	private:
		MouseClickedFlag flag;
		uint32_t button;

	public:
		MouseClickEvent(MouseClickedFlag flag, uint32_t button);

		uint32_t GetMouseButton() const;
		bool IsPressed() const;
		bool IsReleased() const;

		std::string GetInfo() const;
	};

	class MouseMoveEvent : public Event {

	private:
		float xPos;
		float yPos;

	public:
		MouseMoveEvent(float xPos, float yPos);

		float GetX() const;
		float GetY() const;
		
		std::string GetInfo() const;
	};

	class MouseScrollEvent : public Event {

	private:
		float xOffset;
		float yOffset;

	public:
		MouseScrollEvent(float xOffset, float yOffset);

		float GetX() const;
		float GetY() const;

		std::string GetInfo() const;
	};
}


