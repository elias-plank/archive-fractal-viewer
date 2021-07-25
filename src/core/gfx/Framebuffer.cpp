#include "Framebuffer.h"
#include "../../core/Core.h"

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
}