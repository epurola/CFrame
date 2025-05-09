#pragma once 

#include <glm/glm.hpp>

namespace CFrame 
{
	class RenderCommand 
	{
		static void SetClearColor(glm::vec4& color);
		static void Clear();
		static void DrawIndexed(...);
	};
}