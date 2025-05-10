#pragma once
#include <vector>
#include <memory>
#include "Camera2D.h"
#include "../Renderer/Shader.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/IndexBufferr.h"
#include "../Renderer/FrameBuffer.h"
#include "../UIElements/UIElement.h"

namespace CFrame 
{
	struct TextProperties;
	struct OverFlowProperties;

	struct QuadInstance {
		glm::vec2 position;      // x, y
		glm::vec2 size;          // w, h
		glm::vec4 color1;        // primary color (r, g, b, a)
		glm::vec4 color2;        // gradient color (r, g, b, a)
		glm::vec4 borderColor1;  // border gradient start
		glm::vec4 borderColor2;  // border gradient end

		glm::vec4 borderSizes;   
		glm::vec4 radius;        

		float time;
		float speed;
		float angle;
	};

	struct TextInstance 
	{
		float x;
		float y;
		TextProperties props; 
		Texture* atlas; 
		OverFlowProperties overflow;
	};

	struct QuadVertex {
		glm::vec2 position;
		glm::vec2 texCoord;
	};

	class Renderer2D 
	{
	public:
		static void Init(Camera2D& camera);
		static void Begin();
		static void End();
		static void DrawQuad(QuadInstance instance);
		static void DrawTex(TextInstance);
		static void Flush();
		static void RenderText(float x, float y, TextProperties t, Texture* atlas, OverFlowProperties o);

		

	private:
		static Camera2D* s_Camera;
		static std::vector<QuadInstance> quadInstances;
		static std::unique_ptr<Shader> quadShader;
		static std::unique_ptr<VertexArray> VA;
		static std::unique_ptr<VertexBuffer> VB;
		static std::unique_ptr<VertexBuffer> instanceBuffer;
		static std::unique_ptr<IndexBuffer> IB;
		static std::unique_ptr<FrameBuffer> FB;

		static std::vector<TextInstance> text;
		static std::unique_ptr<Shader> textShader;
		static std::unique_ptr<VertexArray> textVA;
		static std::unique_ptr<VertexBuffer> textVB;
		static std::unique_ptr<VertexBufferLayout> textLayout;
		static std::unique_ptr<IndexBuffer> textIndices;
	};
}