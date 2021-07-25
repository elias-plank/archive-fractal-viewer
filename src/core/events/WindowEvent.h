#pragma once
#include "Event.h"

namespace FractalViewer {

	class WindowEvent :	public Event {

	private:
		uint32_t width;
		uint32_t height;

	public:
		WindowEvent(uint32_t width, uint32_t height);

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		std::string GetInfo() const;
	};

}

