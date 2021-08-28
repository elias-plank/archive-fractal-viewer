#pragma once
#include "BufferLayout.h"

namespace FractalViewer {

	class VertexBuffer {

	private:
		uint32_t rendererId;
		BufferLayout layout;

	public:
		VertexBuffer();
		VertexBuffer(const void* data, uint32_t size);
		~VertexBuffer();

		void SetData(const void* data, uint32_t size);
		void SetLayout(const BufferLayout& layout);

		const BufferLayout& GetLayout() const;

		void Bind() const;
		void Unbind() const;
	};
}

