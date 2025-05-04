#pragma once
#include <stdint.h>
#include <memory>
#include "../Window.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBufferr.h" //toDo: Rename this
#include "FrameBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "../UIElements/UIElement.h"
#include "Fontloader.h"


namespace CFrame {

	struct ElementProperties;
	struct TextProperties;
	struct OverFlowProperties;
	struct LineProperties;

	struct TextVertex {
		glm::vec2 position;
		glm::vec2 texCoord;
		glm::vec4 color;
	};

	class Renderer
	{
	public:
		Renderer(Window& window);

		~Renderer();

		void DrawRectangle(float x, float y, float w, float h,
			ElementProperties p, float speed, float time, Texture* texture );

		void RenderText(const std::string& text, float x, float y, TextProperties t, Texture* atlas, OverFlowProperties o);
		void DrawLine(LineProperties p);
		void ClipOverflow(int x, int y, int width, int height, int windowHeight);
		void DisableOverflow();
		void BeginFrame();
		void EndFrame();
		void DrawFullScreenQuad();
		void Resize(int w, int h);
        
		

	private:
		Window& window ;
		std::unique_ptr<Shader> shader = nullptr;
		std::unique_ptr<VertexArray> rectVA = nullptr;
		std::unique_ptr<VertexBuffer> rectVB = nullptr;
		std::unique_ptr<VertexBufferLayout> rectLayout = nullptr;
		std::unique_ptr<IndexBuffer> rectIndices = nullptr;

		std::unique_ptr<Shader> textShader = nullptr;
		std::unique_ptr<VertexArray> textVA = nullptr;
		std::unique_ptr<VertexBuffer> textVB = nullptr;
		std::unique_ptr<VertexBufferLayout> textLayout = nullptr;
		std::unique_ptr<IndexBuffer> textIndices = nullptr;

		std::unique_ptr<Shader> lineShader = nullptr;
		std::unique_ptr<VertexArray> lineVA = nullptr;
		std::unique_ptr<VertexBuffer> lineVB = nullptr;
		std::unique_ptr<VertexBufferLayout> lineLayout = nullptr;
		std::unique_ptr<IndexBuffer> lineIndices = nullptr;

		std::unique_ptr<FrameBuffer> FBO = nullptr;
		std::unique_ptr<Shader> screenShader = nullptr;
		std::unique_ptr<VertexArray> screenVA = nullptr;
		std::unique_ptr<VertexBuffer> screenVB = nullptr;
		std::unique_ptr<VertexBufferLayout> screenLayout = nullptr;
		std::unique_ptr<IndexBuffer> screenIndices = nullptr;

		unsigned int rectIndecies[6] = { 0, 1, 2, 2, 3, 0 };

		
	};

}
