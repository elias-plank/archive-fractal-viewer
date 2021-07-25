#pragma once
#include <glad/glad.h>
#include <cstdint>

namespace FractalViewer {

	class Framebuffer {

	private:
		uint32_t width;
		uint32_t height;
		uint32_t rendererId;
		uint32_t textureId;
		uint32_t frameBufferId;

	public:
		Framebuffer(uint32_t width, uint32_t height);

		void Resize(uint32_t width, uint32_t height);

		void Bind() const;
		void Unbind() const;

		uint32_t GetTextureId() const;
	};
}


