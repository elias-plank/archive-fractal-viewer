#pragma once
#include <glad/glad.h>
#include <fstream>

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
		~Framebuffer();

		void Resize(uint32_t width, uint32_t height);
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		void Bind() const;
		void Unbind() const;

		uint32_t GetTextureId() const;

		void SaveTexture(const std::string& path) const;
	};
}


