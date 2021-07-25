#include "BufferLayout.h"
#include <glad/glad.h>

namespace FractalViewer {

	static void ShaderTypeToOpenGL(ShaderDataType type, uint32_t &count, uint32_t &glType, uint32_t& glStride) {

		switch (type) {

		case ShaderDataType::Int: glType =		GL_INT;		count = 1;		glStride = 1 *		sizeof(int);	break;
		case ShaderDataType::Int2: glType =		GL_INT;		count = 2;		glStride = 2 *		sizeof(int);	break;
		case ShaderDataType::Int3: glType =		GL_INT;		count = 3;		glStride = 3 *		sizeof(int);	break;
		case ShaderDataType::Int4: glType =		GL_INT;		count = 4;		glStride = 4 *		sizeof(int);	break;
		case ShaderDataType::Float: glType =	GL_FLOAT;	count = 1;		glStride = 1 *		sizeof(float);	break;
		case ShaderDataType::Float2: glType =	GL_FLOAT;	count = 2;		glStride = 2 *		sizeof(float);	break;
		case ShaderDataType::Float3: glType =	GL_FLOAT;	count = 3;		glStride = 3 *		sizeof(float);	break;
		case ShaderDataType::Float4: glType =	GL_FLOAT;	count = 4;		glStride = 4 *		sizeof(float);	break;
		case ShaderDataType::Mat4: glType =		GL_FLOAT;	count = 4 * 4;	glStride = 4 * 4 *	sizeof(float);	break;
		}	
	}

	BufferElement::BufferElement(ShaderDataType type, bool normalized) {

		ShaderTypeToOpenGL(type, this->count, this->type, this->stride);
		this->normalized = normalized;
	}

	BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements) {

		this->elements = elements;
	}

	std::vector<BufferElement> BufferLayout::GetElements() const {

		return elements;
	}

	uint32_t BufferLayout::GetTotalStride() const {

		uint32_t stride = 0;

		for (auto& current : elements) {

			stride += current.stride;
		}

		return stride;
	}
}