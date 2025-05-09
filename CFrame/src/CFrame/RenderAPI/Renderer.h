#pragma once

namespace CFrame {
	class Renderer {
	public:
		static void Init();
		static void ShutDown();

		static void BeginFrame();
		static void RenderScene(/*const Scene& scene*/);
		static void EndFrame();

		static void SubmitDrawCommand(/*const DrawCommand cmd*/);
	};
}