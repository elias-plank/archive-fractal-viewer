#include "Renderer.h"

namespace FractalViewer {

	void Renderer::Clear() {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::SetClearColor(const glm::vec4& color) {

		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<ElementBuffer>& elementBuffer, const std::shared_ptr<Shader>& shader, uint32_t mode) {

		shader->Bind();
		vertexArray->Bind();
		elementBuffer->Bind();
		glDrawElements(mode, elementBuffer->GetCount(), GL_UNSIGNED_INT, NULL);
	}
}