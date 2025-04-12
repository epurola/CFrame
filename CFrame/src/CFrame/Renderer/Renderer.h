#pragma once
#include <stdint.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <memory>
#include "../Window.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBufferr.h"
#include "Shader.h"
#include "Texture.h"
#include "../UIElements/UIElement.h"
#include <SDL3/SDL.h>
#include "Fontloader.h"

namespace CFrame {

	struct ElementProperties;

	class Renderer
	{
	public:
		Renderer(Window& window);

		~Renderer();

		void DrawRectangle(float x, float y, float w, float h,
			ElementProperties p, float speed, float time, Texture* texture );

		void RenderText(const std::string& text, float x, float y);
		

	private:
		Window& window;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<Shader> textShader;
		unsigned char* glyph;
		int width, height, xOffset, yOffset;
		unsigned int glyphTexture;
		Texture* texture = nullptr;
		std::map<char, fontInfo> glyphs;
		FontLoader*  fontLoader = nullptr ;
	};
}
