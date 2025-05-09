#pragma once

namespace CFrame 
{
	class Renderer3D 
	{
		static void BeginScene(/*const Camera& camera*/);
		static void EndScene();
		static void SubmitMesh();
	};
}