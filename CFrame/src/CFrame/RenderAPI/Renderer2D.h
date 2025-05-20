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
		float scale = 1.0f;
	};

	struct QuadInstanceT {
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

		Texture* texture;
		ElementProperties p;
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
		static void DrawTextured(QuadInstanceT i);
		static void Flush();
		static void RenderText(float x, float y, TextProperties t, Texture* atlas, OverFlowProperties o);
		static void Renderer2D::DrawRectangle(float x, float y, float w, float h, ElementProperties p, float speed, float time,Texture* texture);
		static void Renderer2D::ClipOverflow(int x, int y, int width, int height, int windowHeight);
		static void Renderer2D::DisableOverflow();

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

		static std::vector<QuadInstanceT> texturedQuads;
		static std::unique_ptr<Shader> shader;
		static std::unique_ptr<VertexArray> rectVA;
		static std::unique_ptr<VertexBuffer> rectVB;
		static std::unique_ptr<VertexBufferLayout> rectLayout;
		static std::unique_ptr<IndexBuffer> rectIndices;
	};
}