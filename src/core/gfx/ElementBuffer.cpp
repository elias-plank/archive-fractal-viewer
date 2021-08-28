#include "ElementBuffer.h"
#include <glad/glad.h>

namespace FractalViewer {

	ElementBuffer::ElementBuffer() {

		count = 0;
		glGenBuffers(1, &rendererId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
	}

	ElementBuffer::ElementBuffer(uint32_t* data, uint32_t count) {

		this->count = count;
		glGenBuffers(1, &rendererId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_DYNAMIC_DRAW);
	}

	ElementBuffer::~ElementBuffer() {

		glDeleteBuffers(1, &rendererId);
	}

	void ElementBuffer::SetData(uint32_t* data, uint32_t count) {

		this->count = count;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_DYNAMIC_DRAW);
	}

	void ElementBuffer::Bind() const {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
	}

	void ElementBuffer::Unbind() const {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
	uint32_t ElementBuffer::GetCount() const {

		return count;
	}
}