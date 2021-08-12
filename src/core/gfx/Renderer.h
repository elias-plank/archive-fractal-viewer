#pragma once
#include "VertexArray.h"
#include "Shader.h"

namespace FractalViewer {

	class Renderer {

	public:
		static void Clear();
		static void SetClearColor(const glm::vec4& color);
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<ElementBuffer>& elementBuffer, const std::shared_ptr<Shader>& shader, uint32_t mode = GL_TRIANGLES);
	};
}


