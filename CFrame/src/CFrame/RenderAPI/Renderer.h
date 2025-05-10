#pragma once
#include <memory>
#include <vector>
#include "Renderer2D.h"
#include "Camera2D.h"  
#include "../Renderer/Shader.h"  
#include "../Renderer/FrameBuffer.h"

namespace CFrame {
	class Renderer {
	public:
		static void Init();
		static void ShutDown();

		static void BeginFrame();
		static void RenderScene(/*const Scene& scene*/);
		static void EndFrame();

		static void SubmitDrawCommand(/*const DrawCommand cmd*/);

	private:
		static std::unique_ptr<Camera2D> Camera2D;  // The camera
		static std::unique_ptr<FrameBuffer> frameBuffer;  // Frame buffer
		static bool render3D;
	};
}