#pragma once
#include <glad/glad.h>

namespace CFrame 
{
	class FrameBuffer 
	{
	private:
		unsigned int RendererId;
		unsigned int TextureId;
		int width, height;

	public:
		FrameBuffer(int width, int height);
		~FrameBuffer();

		void Bind() const;
		void Unbind() const;
	};
}