#include "Framebuffer.h"
#include "../../core/Core.h"

#include <stb_image/stb_image_write.h>

namespace FractalViewer {

	Framebuffer::Framebuffer(uint32_t width, uint32_t height) {

		this->width = width;
		this->height = height;

		glGenFramebuffers(1, &frameBufferId);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);

		glGenRenderbuffers(1, &rendererId);
		glBindRenderbuffer(GL_RENDERBUFFER, rendererId);

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rendererId); // 

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			ASSERT(false, "Framebuffer is not complete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Framebuffer::~Framebuffer() {

		glDeleteFramebuffers(1, &rendererId);
	}

	void Framebuffer::Resize(uint32_t width, uint32_t height) {

		this->width = width;
		this->height = height;
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glBindRenderbuffer(GL_RENDERBUFFER, rendererId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	}

	void Framebuffer::Bind() const {

		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
	}

	void Framebuffer::Unbind() const {

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32_t Framebuffer::GetTextureId() const {

		return textureId;
	}

	void Framebuffer::SaveTexture(const std::string& path) const {

		std::string file = path;

		if (file.find(".png") == std::string::npos) {

			file.append(".png");
		}

		static uint8_t* data = new uint8_t[3 * size_t(width) * size_t(height)];
		memset(reinterpret_cast<void*>(data), 0, 3 * size_t(width) * size_t(height));

		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, reinterpret_cast<void*>(data));

		stbi_flip_vertically_on_write(true);

		ASSERT(stbi_write_png(file.c_str(), width, height, 3, reinterpret_cast<void*>(data), width * 3), "Couldn't save image!");
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		delete[] data;
	}
}