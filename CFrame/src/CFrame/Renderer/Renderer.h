#pragma once
#include <stdint.h>
#include <memory>
#include "../Window.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBufferr.h"
#include "Shader.h"
#include "Texture.h"
#include "../UIElements/UIElement.h"
#include "Fontloader.h"


namespace CFrame {

	struct ElementProperties;
	struct TextProperties;
	struct OverFlowProperties;
	struct LineProperties;

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
        
		

	private:
		Window& window;
		int width, height, xOffset, yOffset;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<VertexArray> rectVA;
		std::unique_ptr<VertexBuffer> rectVB;
		std::unique_ptr<VertexBufferLayout> rectLayout;
		std::unique_ptr<IndexBuffer> rectIndices;

		std::unique_ptr<Shader> textShader;
		std::unique_ptr<VertexArray> textVA;
		std::unique_ptr<VertexBuffer> textVB;
		std::unique_ptr<VertexBufferLayout> textLayout;
		std::unique_ptr<IndexBuffer> textIndices;

		std::unique_ptr<Shader> lineShader;
		std::unique_ptr<VertexArray> lineVA;
		std::unique_ptr<VertexBuffer> lineVB;
		std::unique_ptr<VertexBufferLayout> lineLayout;
		std::unique_ptr<IndexBuffer> lineIndices;

		unsigned int rectIndecies[6] = { 0, 1, 2, 2, 3, 0 };
	};
}
