#pragma once
#include <stdint.h>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include "../Window.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBufferr.h"
#include "Shader.h"
#include "Texture.h"
#include "SDL3/SDL.h"

namespace CFrame {

	class Renderer
	{
	public:
		Renderer(Window& window);

		~Renderer();

		void DrawRectangle(float x, float y, float w, float h, SDL_Color color, float angle, int radius, float scale);

	private:
		Window& window;
		SDL_FRect rect;
		SDL_Texture* texture = NULL;
		SDL_FColor fcolor;
	};
}
