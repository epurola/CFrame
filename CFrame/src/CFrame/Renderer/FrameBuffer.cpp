#include "FrameBuffer.h"
#include "../Log.h"
namespace CFrame 
{
	FrameBuffer::FrameBuffer(int width, int height)
		:width(width), height(height)
	{
		glGenFramebuffers(1, &RendererId);
		glBindFramebuffer(GL_FRAMEBUFFER, RendererId);

		glGenTextures(1, &TextureId);
		glBindTexture(GL_TEXTURE_2D, TextureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TextureId, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteTextures(1, &TextureId);
		glDeleteFramebuffers(1, &RendererId);
	}

	void FrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, RendererId);
		glViewport(0, 0, width, height);
	}

	void FrameBuffer::BindTexture() 
	{
		glBindTexture(GL_TEXTURE_2D, TextureId);
	}

	void FrameBuffer::Resize(int newWidth, int newHeight)
	{
		if (newWidth == width && newHeight == height)
			return;

		width = newWidth;
		height = newHeight;

		glDeleteFramebuffers(1, &RendererId);
		glDeleteTextures(1, &TextureId);

		glGenFramebuffers(1, &RendererId);
		glBindFramebuffer(GL_FRAMEBUFFER, RendererId);

		glGenTextures(1, &TextureId);
		glBindTexture(GL_TEXTURE_2D, TextureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D, TextureId, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

