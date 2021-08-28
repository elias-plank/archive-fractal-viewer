#pragma once
#include "ElementBuffer.h"
#include "VertexBuffer.h"
#include <memory> // shared_ptr

namespace FractalViewer {

	class VertexArray {

	private:
		uint32_t rendererId;
		std::shared_ptr<ElementBuffer> elementBuffer;
		std::shared_ptr<VertexBuffer> vertexBuffer;

	public:
		VertexArray();
		~VertexArray();

		void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer);

		void Bind() const;
		void Unbind() const;
	};
}


