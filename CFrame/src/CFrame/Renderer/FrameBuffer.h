#pragma once
#include <glad/glad.h>

namespace CFrame 
{
	class FrameBuffer 
	{
	private:
		unsigned int RendererId = 0;
		unsigned int TextureId = 0;
		int width = 0;
		int height = 0;

	public:
		FrameBuffer(int width, int height);
		~FrameBuffer();

		void Bind() const;
		void Unbind() const;
		void BindTexture();
		void Resize(int newWidth, int newHeight);
	};
}