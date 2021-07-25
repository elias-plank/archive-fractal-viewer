#pragma once

#include <functional>

namespace FractalViewer {

	class Event {

	public:
		Event() = default;

		virtual std::string GetInfo() const = 0;
	};

	typedef std::function<void(const Event&)> EventFn;
}

