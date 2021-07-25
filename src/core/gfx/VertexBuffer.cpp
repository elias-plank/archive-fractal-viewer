#include "VertexBuffer.h"
#include <glad/glad.h>

namespace FractalViewer {

	VertexBuffer::VertexBuffer() {

		glGenBuffers(1, &rendererId);
		glBindBuffer(GL_ARRAY_BUFFER, rendererId);
	}

	VertexBuffer::VertexBuffer(const void* data, uint32_t size) {

		glGenBuffers(1, &rendererId);
		glBindBuffer(GL_ARRAY_BUFFER, rendererId);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}

	void VertexBuffer::SetData(const void* data, uint32_t size) {

		glBindBuffer(GL_ARRAY_BUFFER, rendererId);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}

	void VertexBuffer::SetLayout(const BufferLayout& layout) {

		this->layout = layout;
	}

	const BufferLayout& VertexBuffer::GetLayout() const {

		return layout;
	}

	void VertexBuffer::Bind() const {

		glBindBuffer(GL_ARRAY_BUFFER, rendererId);
	}

	void VertexBuffer::Unbind() const {

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}