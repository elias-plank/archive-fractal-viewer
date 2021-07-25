#include "VertexArray.h"
#include "../Core.h"
#include <glad/glad.h>

namespace FractalViewer {

	VertexArray::VertexArray() {

		glGenVertexArrays(1, &rendererId);
	}

	void VertexArray::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {

		glBindVertexArray(rendererId);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		uint32_t index = 0;
		uint32_t offset = 0;
		uint32_t stride = layout.GetTotalStride();

		for (auto& current : layout.GetElements()) {

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, current.count, current.type, current.normalized ? GL_TRUE : GL_FALSE, stride, (const void*)offset);

			offset += current.stride;
			index++;
		}

		this->vertexBuffer = vertexBuffer;
	}

	void VertexArray::SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer) {

		glBindVertexArray(rendererId);
		elementBuffer->Bind();
		this->elementBuffer = elementBuffer;
	}

	void VertexArray::Bind() const {

		glBindVertexArray(rendererId);
	}

	void VertexArray::Unbind() const {

		glBindVertexArray(0);
	}
}