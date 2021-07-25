#pragma once
#include <cstdint>

namespace FractalViewer {

	class ElementBuffer {

	private:
		uint32_t rendererId;
		uint32_t count;

	public:
		ElementBuffer();
		ElementBuffer(uint32_t* data, uint32_t count);

		void SetData(uint32_t* data, uint32_t count);

		void Bind() const;
		void Unbind() const;

		uint32_t GetCount() const;
	};
}


