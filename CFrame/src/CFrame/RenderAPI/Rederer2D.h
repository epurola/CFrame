#pragma once

namespace CFrame 
{
	class Renderer2D 
	{
		static void Begin();
		static void End();
		static void DrawQuad(...);
		static void Flush();
	};
}